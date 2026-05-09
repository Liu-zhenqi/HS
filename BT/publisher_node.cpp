// 基本 ROS2 头文件
#include "rclcpp/rclcpp.hpp"

// 根据消息类型包含相应的头文件
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "sensor_msgs/msg/image.hpp"

// 时间相关
#include "builtin_interfaces/msg/time.hpp"

// 如果需要使用 QoS
#include "rclcpp/qos.hpp"
#include <vector>
class mypublisher : public rclcpp::Node{
    public:
    mypublisher() : Node("my_publisher")
    {
        publisher_ = create_publisher<std_msgs::msg::Int32>("blood",10);
        timer_ = this->create_wall_timer(
      500ms,  // 500毫秒
      std::bind(&MyPublisher::timer_callback, this)
    );

    }
    private:
  void timer_callback()
  {
    
    RCLCPP_INFO(this->get_logger(), "Publishing: blood = '%d'", message.data);
    publisher_->publish(message);
  }
  
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  auto message = std_msgs::msg::int32();
  message = 100;
}