cmake_minimum_required(VERSION 3.5)
project(pubsub)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)

set(dependencies
  rclcpp
  rclcpp_action
  std_msgs
  example_interfaces
)

# C++ deadline_sub

add_executable(deadline_sub
  src/deadline_sub.cpp
)

ament_target_dependencies(deadline_sub
  ${dependencies}
)

install(TARGETS deadline_sub
  DESTINATION lib/${PROJECT_NAME})

# action server and client

add_executable(simple_action_server
  src/simple_action_server.cpp
)

ament_target_dependencies(simple_action_server
  ${dependencies}
)

install(TARGETS simple_action_server
  DESTINATION lib/${PROJECT_NAME})

add_executable(spam_action_client
  src/spam_action_client.cpp
)

ament_target_dependencies(spam_action_client
  ${dependencies}
)

install(TARGETS spam_action_client
  DESTINATION lib/${PROJECT_NAME})

# Launch
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

# Python package
ament_python_install_package(${PROJECT_NAME})

# Testing

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
  find_package(ament_cmake_gtest REQUIRED)
endif()

ament_export_include_directories(include)
ament_export_dependencies(${dependencies})
ament_package()

