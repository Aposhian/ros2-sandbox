#!/usr/bin/env python3

from queue import Queue, Empty

import rclpy
from std_msgs.msg import Int32


def main(args=None):
    rclpy.init(args=args)
    node = rclpy.create_node("sub")
    node.declare_parameter('num')

    message_queue = Queue()

    def message_generator():
        while True:
            rclpy.spin_once(node)
            try:
                yield message_queue.get_nowait()
            except Empty:
                continue

    node.create_subscription(
        Int32,
        'boring_int',
        lambda msg: message_queue.put(msg),
        10
    )

    for msg in message_generator():
        print(msg.data)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
