#include <stdint.h>

#include <iostream>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

using namespace std::literals::chrono_literals;  // NOLINT

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("deadline_sub");

    int32_t value;

    rclcpp::SubscriptionOptions options;
    options.event_callbacks.deadline_callback = [&](auto & /*info*/) {
        std::cout << "Deadline exceeded!\n";
    };

    auto sub = node->create_subscription<std_msgs::msg::Int32>(
        "boring_int",
        rclcpp::QoS(1)
            .reliability(rclcpp::ReliabilityPolicy::BestEffort)
            .deadline(rclcpp::Duration(1s)),
        [&](std_msgs::msg::Int32::SharedPtr msg) {
            value = msg->data;
        },
        options
    );

    rclcpp::spin(node);
    return 0;
}