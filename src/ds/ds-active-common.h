// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include "device.h"
#include "core/video.h"
#include "ds/ds-device-common.h"
#include "ds-private.h"

namespace librealsense
{
    class ds_active_common
    {
    public:
        ds_active_common(uvc_sensor& raw_color_ep,
            synthetic_sensor& color_ep,
            device* owner, 
            ds::d400_caps device_capabilities);
        void register_options();

    private:
        uvc_sensor& _raw_depth_ep;
        synthetic_sensor& _depth_ep;
        device* _owner;
        ds::d400_caps _device_capabilities;
    };

    

}
