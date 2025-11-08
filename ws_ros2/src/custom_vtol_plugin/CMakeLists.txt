cmake_minimum_required(VERSION 3.8)
project(custom_vtol_plugin)

# Compiler warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- ROS 2 ---
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(gazebo_ros REQUIRED)                    # Added

# --- Ignition (Gazebo Garden) ---
find_package(ignition-cmake2 REQUIRED)

# === PATCH: Block fuel tools but keep gazebo6 ===
list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/patch")

find_package(ignition-common4 REQUIRED)
find_package(ignition-math6 REQUIRED)
find_package(ignition-gazebo6 REQUIRED)  # Uses our patched config

# --- Custom Messages ---
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MotorCommands.msg"
  DEPENDENCIES std_msgs
)

# --- Plugin Library ---
add_library(motor_controller_plugin SHARED
  src/motor_controller_plugin.cpp
)

# Include directories (modern way)
target_include_directories(motor_controller_plugin PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp>
  $<INSTALL_INTERFACE:include>
)

# Link ROS 2 + Ignition (modern target syntax)
ament_target_dependencies(motor_controller_plugin
  rclcpp
  gazebo_ros
  std_msgs
)

target_link_libraries(motor_controller_plugin
  ignition-common4::ignition-common4
  ignition-math6::ignition-math6
  ignition-gazebo6::ignition-gazebo6
)

# Ensure messages are built first
add_dependencies(motor_controller_plugin ${PROJECT_NAME}__rosidl_generator_cpp)

# --- Install ---
install(TARGETS motor_controller_plugin
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp/custom_vtol_plugin
  DESTINATION include/custom_vtol_plugin
)

ament_package()