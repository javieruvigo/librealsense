// Generated by gencpp from file realsense_legacy_msgs/motion_stream_info.msg
// DO NOT EDIT!


#ifndef realsense_legacy_msgs_MESSAGE_MOTION_STREAM_INFO_H
#define realsense_legacy_msgs_MESSAGE_MOTION_STREAM_INFO_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <realsense_legacy_msgs/motion_intrinsics.h>
#include <realsense_legacy_msgs/stream_extrinsics.h>

namespace realsense_legacy_msgs
{
template <class ContainerAllocator>
struct motion_stream_info_
{
  typedef motion_stream_info_<ContainerAllocator> Type;

  motion_stream_info_()
    : motion_type()
    , fps(0)
    , stream_intrinsics()
    , stream_extrinsics()  {
    }
  motion_stream_info_(const ContainerAllocator& _alloc)
    : motion_type(_alloc)
    , fps(0)
    , stream_intrinsics(_alloc)
    , stream_extrinsics(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _motion_type_type;
  _motion_type_type motion_type;

   typedef uint32_t _fps_type;
  _fps_type fps;

   typedef  ::realsense_legacy_msgs::motion_intrinsics_<ContainerAllocator>  _stream_intrinsics_type;
  _stream_intrinsics_type stream_intrinsics;

   typedef  ::realsense_legacy_msgs::stream_extrinsics_<ContainerAllocator>  _stream_extrinsics_type;
  _stream_extrinsics_type stream_extrinsics;




  typedef std::shared_ptr< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> > Ptr;
  typedef std::shared_ptr< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> const> ConstPtr;

}; // struct motion_stream_info_

typedef ::realsense_legacy_msgs::motion_stream_info_<std::allocator<void> > motion_stream_info;

typedef std::shared_ptr< ::realsense_legacy_msgs::motion_stream_info > motion_stream_infoPtr;
typedef std::shared_ptr< ::realsense_legacy_msgs::motion_stream_info const> motion_stream_infoConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> & v)
{
rs2rosinternal::message_operations::Printer< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace realsense_legacy_msgs

namespace rs2rosinternal
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'realsense_legacy_msgs': ['/home/administrator/ros/realsense_sdk_internal/sdk_internal/tools/realsense_legacy_msgs_generator/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> const>
  : std::false_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
  : std::true_type
  { };

template <class ContainerAllocator>
struct IsMessage< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> const>
  : std::true_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
  : std::false_type
  { };

template <class ContainerAllocator>
struct HasHeader< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> const>
  : std::false_type
  { };


template<class ContainerAllocator>
struct MD5Sum< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "02cc8b81050aeef9ff36df30d8eacb2d";
  }

  static const char* value(const ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x02cc8b81050aeef9ULL;
  static const uint64_t static_value2 = 0xff36df30d8eacb2dULL;
};

template<class ContainerAllocator>
struct DataType< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "realsense_legacy_msgs/motion_stream_info";
  }

  static const char* value(const ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string motion_type\n\
uint32 fps\n\
realsense_legacy_msgs/motion_intrinsics stream_intrinsics\n\
realsense_legacy_msgs/stream_extrinsics stream_extrinsics\n\
\n\
\n\
================================================================================\n\
MSG: realsense_legacy_msgs/motion_intrinsics\n\
float32[12] data\n\
float32[3] noise_variances\n\
float32[3] bias_variances\n\
\n\
================================================================================\n\
MSG: realsense_legacy_msgs/stream_extrinsics\n\
realsense_legacy_msgs/extrinsics extrinsics\n\
uint64 reference_point_id\n\
\n\
================================================================================\n\
MSG: realsense_legacy_msgs/extrinsics\n\
float32[9] rotation    # column-major 3x3 rotation matrix \n\
float32[3] translation # 3 element translation vector, in meters \n\
";
  }

  static const char* value(const ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace rs2rosinternal

namespace rs2rosinternal
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.motion_type);
      stream.next(m.fps);
      stream.next(m.stream_intrinsics);
      stream.next(m.stream_extrinsics);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct motion_stream_info_

} // namespace serialization
} // namespace rs2rosinternal

namespace rs2rosinternal
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::realsense_legacy_msgs::motion_stream_info_<ContainerAllocator>& v)
  {
    s << indent << "motion_type: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.motion_type);
    s << indent << "fps: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.fps);
    s << indent << "stream_intrinsics: ";
    s << std::endl;
    Printer< ::realsense_legacy_msgs::motion_intrinsics_<ContainerAllocator> >::stream(s, indent + "  ", v.stream_intrinsics);
    s << indent << "stream_extrinsics: ";
    s << std::endl;
    Printer< ::realsense_legacy_msgs::stream_extrinsics_<ContainerAllocator> >::stream(s, indent + "  ", v.stream_extrinsics);
  }
};

} // namespace message_operations
} // namespace rs2rosinternal

#endif // realsense_legacy_msgs_MESSAGE_MOTION_STREAM_INFO_H
