#include <chrono>
#include <thread>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <example_interfaces/action/fibonacci.hpp>

using Action = example_interfaces::action::Fibonacci;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>("simple_action_server");

  rclcpp::TimerBase::SharedPtr goal_timer;

  auto action_server = rclcpp_action::create_server<Action>(
    node,
    "/test_action",
    [node](
      const rclcpp_action::GoalUUID &,
      std::shared_ptr<const Action::Goal>)
    {
      RCLCPP_INFO(node->get_logger(), "Goal received");
      return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    },
    [node](const
    std::shared_ptr<rclcpp_action::ServerGoalHandle<Action>>)
    {
      RCLCPP_INFO(node->get_logger(), "Goal cancelled");
      return rclcpp_action::CancelResponse::ACCEPT;
    },
    [node, &goal_timer](
      const
      std::shared_ptr<rclcpp_action::ServerGoalHandle<Action>>
      goal_handle
    )
    {
      RCLCPP_INFO(node->get_logger(), "Executing goal");
      goal_timer = node->create_wall_timer(
        std::chrono::milliseconds(2000),
        [goal_handle, node, &goal_timer]()
        {
          RCLCPP_INFO(node->get_logger(), "Ticking goal");
          if (rclcpp::ok()) {
            auto result = std::make_shared<Action::Result>();
            if (goal_handle->is_canceling()) {
              goal_handle->canceled(result);
              RCLCPP_INFO(node->get_logger(), "Goal canceled ");
              goal_timer->cancel();
            } else {
              std::this_thread::sleep_for(std::chrono::milliseconds(100));
              goal_handle->succeed(std::make_shared<Action::Result>());
            }
          }
        }
      );
    }
  );

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}