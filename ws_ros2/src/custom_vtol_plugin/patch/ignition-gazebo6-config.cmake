# /home/parsa/ws_ros2/src/custom_vtol_plugin/patch/ignition-gazebo6-config.cmake

# === PATCH: Prevent ignition-fuel_tools7 from loading ===
# But keep ignition-gazebo6 itself working

# 1. Block fuel tools
set(IGNITION-FUEL_TOOLS7_FOUND FALSE CACHE INTERNAL "Disabled by custom_vtol_plugin")
set(IGNITION_FUEL_TOOLS7_FOUND FALSE CACHE INTERNAL "Disabled by custom_vtol_plugin")

# 2. Intercept find_package calls
macro(find_package)
  if(${ARGV0} MATCHES "ignition-fuel_tools7" OR ${ARGV0} MATCHES "IGNITION-FUEL_TOOLS7")
    set(${ARGV0}_FOUND FALSE)
    return()
  endif()
  _find_package(${ARGV})
endmacro()

# 3. Now safely include the REAL ignition-gazebo6 config
include("/usr/lib/x86_64-linux-gnu/cmake/ignition-gazebo6/ignition-gazebo6-config.cmake" OPTIONAL RESULT_VARIABLE _gz_config)
if(NOT _gz_config)
  message(FATAL_ERROR "Failed to find real ignition-gazebo6-config.cmake")
endif()