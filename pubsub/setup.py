from setuptools import setup

import os
from glob import glob

package_name = 'pubsub'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py'))
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Adam Aposhian',
    maintainer_email='aposhian.dev@gmail.com',
    description='Simple nodes to test publications and subscriptions',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'pub = pubsub.pub:main',
            'sub = pubsub.sub:main',
            'generator_sub = pubsub.generator_sub:main'
        ],
    },
)
