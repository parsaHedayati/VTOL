cmake_minimum_required(VERSION 3.8)
project(custom_vtol_plugin LANGUAGES CXX C)

# Fix JsonCpp namespace conflict
set(JSONCPP_SKIP_LEGACY_NAMESPACE ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ================== ROS 2 ==================
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ros_gz_sim REQUIRED)

# ================== Gazebo Harmonic ==================
find_package(gz-cmake3 REQUIRED)
find_package(gz-sim8 REQUIRED)
find_package(gz-math8 REQUIRED)
find_package(gz-common5 REQUIRED)
find_package(gz-plugin2 REQUIRED)
find_package(gz-msgs9 REQUIRED)

# ================== Generate Messages ==================
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MotorCommands.msg"
  DEPENDENCIES std_msgs
)
ament_export_dependencies(rosidl_default_runtime)
# ================== Build Plugin ==================
add_library(motor_controller_plugin SHARED
  src/motor_controller_plugin.cpp
)
target_include_directories(motor_controller_plugin PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

ament_target_dependencies(motor_controller_plugin
  rclcpp
  std_msgs
  ros_gz_sim
)

target_link_libraries(motor_controller_plugin
  gz-sim8::gz-sim8
  gz-math8::gz-math8
  gz-common5::gz-common5
  gz-plugin2::gz-plugin2
  gz-msgs9::gz-msgs9  
)

# Make sure messages are built before plugin
add_dependencies(motor_controller_plugin ${PROJECT_NAME}__rosidl_generator_cpp)

# Link generated message typesupport
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(motor_controller_plugin ${cpp_typesupport_target})

# ================== Install ==================
install(TARGETS motor_controller_plugin
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp/
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

install(PROGRAMS scripts/hover_publisher.py
  DESTINATION lib/${PROJECT_NAME}
)
install(PROGRAMS scripts/hover_control.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()