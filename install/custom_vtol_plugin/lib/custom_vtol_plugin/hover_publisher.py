#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

try:
    from custom_vtol_plugin.msg import MotorCommands
except ImportError:
    print("FATAL ERROR: Could not import MotorCommands message. Ensure the C++ package compiled successfully and environment is sourced.")
    exit(1)


class HoverPublisher(Node):
    def __init__(self):
        super().__init__('hover_command_publisher')

        # Use reliable QoS for safety
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )

        self.publisher_ = self.create_publisher(
            MotorCommands, '/motor_vtol/motor_commands', qos_profile
        )

        # Timer at 200 Hz (5 ms)
        self.timer = self.create_timer(0.005, self.timer_callback)
        self.counter = 0

        # Default hover values (can be tuned)
        self.hover_value = 1550
        self.motor_count = 5

        self.get_logger().info(f'Hover Publisher Initialized at 200 Hz for {self.motor_count} motors.')

    def timer_callback(self):
        msg = MotorCommands()
        msg.motor_values = [self.hover_value] * self.motor_count
        self.publisher_.publish(msg)

        self.counter += 1
        if self.counter % 200 == 0:
            self.get_logger().info(f'Publishing hover command: {msg.motor_values}')


def main(args=None):
    rclpy.init(args=args)
    node = HoverPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
