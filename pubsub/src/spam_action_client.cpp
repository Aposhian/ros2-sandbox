#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <example_interfaces/action/fibonacci.hpp>

using Action = example_interfaces::action::Fibonacci;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp::Node>("spam_action_client");
  auto action_client = rclcpp_action::create_client<Action>(
    node,
    "/test_action"
  );

  rclcpp_action::Client<Action>::SendGoalOptions send_goal_options;

  send_goal_options.goal_response_callback = [node](rclcpp_action::ClientGoalHandle<Action>::SharedPtr){
    RCLCPP_INFO(node->get_logger(), "Goal response received");
  };
  send_goal_options.feedback_callback = [node](rclcpp_action::ClientGoalHandle<Action>::SharedPtr,
  const std::shared_ptr<const Action::Feedback>){
    RCLCPP_INFO(node->get_logger(), "Goal feedback received");
  };
  send_goal_options.result_callback = [node](const rclcpp_action::ClientGoalHandle<Action>::WrappedResult &){
    RCLCPP_INFO(node->get_logger(), "Goal result received");
  };

  auto thread = std::thread([node, action_client, send_goal_options](){
    while (true) {
      RCLCPP_INFO(node->get_logger(), "Sending goal");
      action_client->async_send_goal(Action::Goal(), send_goal_options);
      action_client->async_send_goal(Action::Goal(), send_goal_options);
      RCLCPP_INFO(node->get_logger(), "Goal sent");
      action_client->async_cancel_all_goals([node](Action::Impl::CancelGoalService::Response::SharedPtr) {
        RCLCPP_INFO(node->get_logger(), "Goal cancel response received");
      });
      action_client->async_cancel_all_goals([node](Action::Impl::CancelGoalService::Response::SharedPtr) {
        RCLCPP_INFO(node->get_logger(), "Goal cancel response received");
      });
      RCLCPP_INFO(node->get_logger(), "Cancel request sent.");
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  });

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}