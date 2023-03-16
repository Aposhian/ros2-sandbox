#!/usr/bin/env python3

"""Run an action server and an action client that deadlocks."""

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            Node(
                package="pubsub",
                # prefix="terminator --execute gdb --args",
                executable="simple_action_server",
                name="simple_action_server",
            ),
            Node(
                package="pubsub",
                executable="spam_action_client",
                name="spam_action_client",
            ),
        ]
    )
