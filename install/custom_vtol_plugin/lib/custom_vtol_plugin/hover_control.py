import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray

class HoverController(Node):
    def __init__(self):
        super().__init__('hover_controller')
        self.pub = self.create_publisher(Float64MultiArray,
                                         '/ros_motor_command',
                                         10)
        self.timer = self.create_timer(0.1, self.publish_hover)

    def publish_hover(self):
        msg = Float64MultiArray()
        msg.data = [1500.0, 1500.0, 1500.0, 1500.0, 0.0]
        self.pub.publish(msg)
        self.get_logger().info(f"Published hover command: {msg.data}")

def main():
    rclpy.init()
    node = HoverController()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
