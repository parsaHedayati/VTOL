import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray

from gz.transport import Node as GzNode
from gz.msgs.double_v_pb2 import Double_V

class CustomBridge(Node):
    def __init__(self):
        super().__init__('custom_bridge')
        self.sub = self.create_subscription(Float64MultiArray,
                                            '/ros_motor_command',
                                            self.callback,
                                            10)
        self.gz_node = GzNode()
        self.pub = self.gz_node.advertise('/model/standard_vtol/command/motor_speed', Double_V)

    def callback(self, msg):
        gz_msg = Double_V()
        gz_msg.data.extend(msg.data)
        self.pub.publish(gz_msg)
        self.get_logger().info(f"Bridged {msg.data} → Gazebo Double_V")

def main():
    rclpy.init()
    node = CustomBridge()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
