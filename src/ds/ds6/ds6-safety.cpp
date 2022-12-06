// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#include "ds6-safety.h"

#include <mutex>
#include <chrono>
#include <vector>
#include <map>
#include <iterator>
#include <cstddef>

#include "ds/ds-timestamp.h"
#include "ds/ds-options.h"
#include "stream.h"

namespace librealsense
{
    const std::map<uint32_t, rs2_format> safety_fourcc_to_rs2_format = {
        {rs_fourcc('R','A','W','8'), RS2_FORMAT_RAW8}
    };
    const std::map<uint32_t, rs2_stream> safety_fourcc_to_rs2_stream = {
        {rs_fourcc('R','A','W','8'), RS2_STREAM_SAFETY}
    };

    ds6_safety::ds6_safety(std::shared_ptr<context> ctx,
        const platform::backend_device_group& group)
        : device(ctx, group), ds6_device(ctx, group),
        _safety_stream(new stream(RS2_STREAM_SAFETY))
    {
        using namespace ds;
        const uint32_t safety_stream_end_point = 9;
        auto safety_devs_info = filter_by_mi(group.uvc_devices, safety_stream_end_point);
        if (safety_devs_info.size() != 1)
            throw invalid_value_exception(to_string() << "RS4XX with Safety models are expected to include a single safety device! - "
                << safety_devs_info.size() << " found");

        auto safety_ep = create_safety_device(ctx, safety_devs_info);
        _safety_device_idx = add_sensor(safety_ep);
    }

    std::shared_ptr<synthetic_sensor> ds6_safety::create_safety_device(std::shared_ptr<context> ctx,
        const std::vector<platform::uvc_device_info>& safety_devices_info)
    {
        using namespace ds;
        auto&& backend = ctx->get_backend();

        std::unique_ptr<frame_timestamp_reader> ds5_timestamp_reader_backup(new ds_timestamp_reader(backend.create_time_service()));
        std::unique_ptr<frame_timestamp_reader> ds5_timestamp_reader_metadata(new ds_timestamp_reader_from_metadata(std::move(ds5_timestamp_reader_backup)));

        auto enable_global_time_option = std::shared_ptr<global_time_option>(new global_time_option());
        auto raw_safety_ep = std::make_shared<uvc_sensor>("Raw Safety Device",
            backend.create_uvc_device(safety_devices_info.front()),
            std::unique_ptr<frame_timestamp_reader>(new global_timestamp_reader(std::move(ds5_timestamp_reader_metadata), _tf_keeper, enable_global_time_option)),
            this);

        auto safety_ep = std::make_shared<ds6_safety_sensor>(this,
            raw_safety_ep,
            safety_fourcc_to_rs2_format,
            safety_fourcc_to_rs2_stream);

        safety_ep->register_option(RS2_OPTION_GLOBAL_TIME_ENABLED, enable_global_time_option);

        safety_ep->register_info(RS2_CAMERA_INFO_PHYSICAL_PORT, safety_devices_info.front().device_path);

        // register options
        register_options(safety_ep);

        // register metadata
        register_metadata(raw_safety_ep);

        // register processing blocks
        register_processing_blocks(safety_ep);
        
        return safety_ep;
    }


    void ds6_safety::register_options(std::shared_ptr<ds6_safety_sensor> safety_ep)
    {
        // empty
    }

    void ds6_safety::register_metadata(std::shared_ptr<uvc_sensor> raw_safety_ep)
    {
        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_FRAME_TIMESTAMP, 
            make_uvc_header_parser(&platform::uvc_header::timestamp));

        // attributes of md_safety_mode
        auto md_prop_offset = offsetof(metadata_raw, mode) +
            offsetof(md_safety_mode, intel_safety_info);

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_FRAME_COUNTER, 
            make_attribute_parser(&md_safety_info::frame_counter, 
                md_safety_info_attributes::frame_counter_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_DEPTH_FRAME_COUNTER,
            make_attribute_parser(&md_safety_info::depth_frame_counter, 
                md_safety_info_attributes::depth_frame_counter_attribute, md_prop_offset));
        
        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SENSOR_TIMESTAMP,
            make_attribute_parser(&md_safety_info::frame_timestamp, 
                md_safety_info_attributes::frame_timestamp_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_LEVEL1,
            make_attribute_parser(&md_safety_info::level1_signal, 
                md_safety_info_attributes::level1_signal_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_LEVEL1_ORIGIN,
            make_attribute_parser(&md_safety_info::level1_frame_counter_origin, 
                md_safety_info_attributes::level1_frame_counter_origin_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_LEVEL2,
            make_attribute_parser(&md_safety_info::level2_signal, 
                md_safety_info_attributes::level2_signal_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_LEVEL2_ORIGIN,
            make_attribute_parser(&md_safety_info::level2_frame_counter_origin, 
                md_safety_info_attributes::level2_frame_counter_origin_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_LEVEL1_VERDICT,
            make_attribute_parser(&md_safety_info::level1_verdict, 
                md_safety_info_attributes::level1_verdict_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_LEVEL2_VERDICT,
            make_attribute_parser(&md_safety_info::level2_verdict, 
                md_safety_info_attributes::level2_verdict_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_HUMAN_VOTE_RESULT,
            make_attribute_parser(&md_safety_info::human_safety_vote_result, 
                md_safety_info_attributes::human_safety_vote_result_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_HARA_EVENTS,
            make_attribute_parser(&md_safety_info::hara_events, 
                md_safety_info_attributes::hara_events_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_SOC_FUSA_EVENTS,
            make_attribute_parser(&md_safety_info::soc_fusa_events, 
                md_safety_info_attributes::soc_fusa_events_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_SOC_FUSA_ACTION,
            make_attribute_parser(&md_safety_info::soc_fusa_action, 
                md_safety_info_attributes::soc_fusa_action_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_FUSA_EVENT,
            make_attribute_parser(&md_safety_info::mb_fusa_event, 
                md_safety_info_attributes::mb_fusa_event_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_FUSA_ACTION,
            make_attribute_parser(&md_safety_info::mb_fusa_action, 
                md_safety_info_attributes::mb_fusa_action_attribute, md_prop_offset));

        raw_safety_ep->register_metadata(RS2_FRAME_METADATA_SAFETY_CRC32,
            make_attribute_parser(&md_safety_info::crc32,
                md_safety_info_attributes::crc32_attribute, md_prop_offset,
                [](const rs2_metadata_type& param) {
                    // compute crc and check validity
                    // TODO - REMI - check next line works well during integration - alignement of struct md_safety_info to 4 is needed
                    uint8_t* start_of_md_struct = reinterpret_cast<uint8_t*>(&const_cast<rs2_metadata_type&>(param)) - sizeof(md_safety_info) + sizeof(param);
                    auto computed_crc32 = calc_crc32(start_of_md_struct, sizeof(md_safety_info) - sizeof(md_safety_info::crc32));
                    return (param == computed_crc32);
                }));
    }

    void ds6_safety::register_processing_blocks(std::shared_ptr<ds6_safety_sensor> safety_ep)
    {
        safety_ep->register_processing_block(processing_block_factory::create_id_pbf(RS2_FORMAT_RAW16, RS2_STREAM_SAFETY));
    }


    stream_profiles ds6_safety_sensor::init_stream_profiles()
    {
        auto lock = environment::get_instance().get_extrinsics_graph().lock();
        auto results = synthetic_sensor::init_stream_profiles();

        for (auto p : results)
        {
            // Register stream types
            if (p->get_stream_type() == RS2_STREAM_SAFETY)
                assign_stream(_owner->_safety_stream, p);
        }

        return results;
    }
}
