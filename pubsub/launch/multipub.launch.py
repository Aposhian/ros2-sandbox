#!/usr/bin/env python3

"""Launch file to run multiple publishers to the same topic"""

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    NUM_PUBLISHERS = 3

    nodes = [
        Node(
            package='pubsub',
            executable='pub',
            name=f'pub_{i}',
            parameters=[
                { 'num': i }
            ]
        )
        for i in range(NUM_PUBLISHERS)
    ]

    return LaunchDescription(nodes)
