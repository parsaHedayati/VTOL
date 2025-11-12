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

        # Fixed topic with namespace from your SDF
        self.publisher_ = self.create_publisher(
            MotorCommands, '/motor_vtol/motor_commands', qos_profile
        )

        self.timer = self.create_timer(0.005, self.timer_callback)
        self.counter = 0
        self.get_logger().info('Hover Publisher Initialized at 200 Hz.')

    def timer_callback(self):
        msg = MotorCommands()
        # Safe to use plain list
        msg.motor_values = [1550, 1550, 1550, 1550]  # Adjust if needed for hover
        self.publisher_.publish(msg)

        self.counter += 1
        if self.counter % 200 == 0:
            self.get_logger().info('Publishing hover command...')


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
