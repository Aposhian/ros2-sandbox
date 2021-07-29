#!/usr/bin/env python3

import rclpy
from std_msgs.msg import Int32

def publish(publisher, num):
    msg = Int32()
    msg.data = int(num)
    publisher.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = rclpy.create_node("multipub")
    node.declare_parameter('num')

    pub = node.create_publisher(Int32, 'boring_int', rclpy.qos.QoSProfile(depth=1, reliability=rclpy.qos.ReliabilityPolicy.RMW_QOS_POLICY_RELIABILITY_RELIABLE, durability=rclpy.qos.DurabilityPolicy.RMW_QOS_POLICY_DURABILITY_VOLATILE))

    node.create_timer(1.0, lambda: publish(pub, node.get_parameter('num').value))

    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
