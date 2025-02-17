// Generated by gencpp from file action_pure/purePursuitResult.msg
// DO NOT EDIT!


#ifndef ACTION_PURE_MESSAGE_PUREPURSUITRESULT_H
#define ACTION_PURE_MESSAGE_PUREPURSUITRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace action_pure
{
template <class ContainerAllocator>
struct purePursuitResult_
{
  typedef purePursuitResult_<ContainerAllocator> Type;

  purePursuitResult_()
    : realPathx()
    , realPathy()  {
    }
  purePursuitResult_(const ContainerAllocator& _alloc)
    : realPathx(_alloc)
    , realPathy(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _realPathx_type;
  _realPathx_type realPathx;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _realPathy_type;
  _realPathy_type realPathy;





  typedef boost::shared_ptr< ::action_pure::purePursuitResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::action_pure::purePursuitResult_<ContainerAllocator> const> ConstPtr;

}; // struct purePursuitResult_

typedef ::action_pure::purePursuitResult_<std::allocator<void> > purePursuitResult;

typedef boost::shared_ptr< ::action_pure::purePursuitResult > purePursuitResultPtr;
typedef boost::shared_ptr< ::action_pure::purePursuitResult const> purePursuitResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::action_pure::purePursuitResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::action_pure::purePursuitResult_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::action_pure::purePursuitResult_<ContainerAllocator1> & lhs, const ::action_pure::purePursuitResult_<ContainerAllocator2> & rhs)
{
  return lhs.realPathx == rhs.realPathx &&
    lhs.realPathy == rhs.realPathy;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::action_pure::purePursuitResult_<ContainerAllocator1> & lhs, const ::action_pure::purePursuitResult_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace action_pure

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::action_pure::purePursuitResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::action_pure::purePursuitResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::action_pure::purePursuitResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::action_pure::purePursuitResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_pure::purePursuitResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::action_pure::purePursuitResult_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::action_pure::purePursuitResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "5f5a82d337935d15760ba2d8cf3e2b56";
  }

  static const char* value(const ::action_pure::purePursuitResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x5f5a82d337935d15ULL;
  static const uint64_t static_value2 = 0x760ba2d8cf3e2b56ULL;
};

template<class ContainerAllocator>
struct DataType< ::action_pure::purePursuitResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "action_pure/purePursuitResult";
  }

  static const char* value(const ::action_pure::purePursuitResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::action_pure::purePursuitResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"\n"
"# result\n"
"float32[] realPathx       # 实际跟踪路径\n"
"float32[] realPathy\n"
"\n"
;
  }

  static const char* value(const ::action_pure::purePursuitResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::action_pure::purePursuitResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.realPathx);
      stream.next(m.realPathy);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct purePursuitResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::action_pure::purePursuitResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::action_pure::purePursuitResult_<ContainerAllocator>& v)
  {
    s << indent << "realPathx[]" << std::endl;
    for (size_t i = 0; i < v.realPathx.size(); ++i)
    {
      s << indent << "  realPathx[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.realPathx[i]);
    }
    s << indent << "realPathy[]" << std::endl;
    for (size_t i = 0; i < v.realPathy.size(); ++i)
    {
      s << indent << "  realPathy[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.realPathy[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ACTION_PURE_MESSAGE_PUREPURSUITRESULT_H
