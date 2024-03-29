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
find_package(std_msgs REQUIRED)

set(dependencies
  rclcpp
  std_msgs
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

