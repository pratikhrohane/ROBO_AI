# panels/imu_panel.py

from PyQt5.QtWidgets import QWidget, QVBoxLayout, QLabel
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt

import pyqtgraph as pg
import pyqtgraph.opengl as gl
import numpy as np


class IMUPanel(QWidget):
    def __init__(self):
        super().__init__()

        layout = QVBoxLayout()
        layout.setAlignment(Qt.AlignTop)

        # 1. Accel and Gyro Labels
        self.accel_label = QLabel("Accel: x: 0.00, y: 0.00, z: 0.00")
        self.gyro_label = QLabel("Gyro : x: 0.00, y: 0.00, z: 0.00")

        for label in [self.accel_label, self.gyro_label]:
            label.setFont(QFont("Consolas", 8))
            label.setStyleSheet("color: lightgray;")

        layout.addWidget(self.accel_label)
        layout.addWidget(self.gyro_label)

        # 2. 3D View: TF-style axis
        self.view = gl.GLViewWidget()
        self.view.opts['distance'] = 5
        self.view.setFixedHeight(200)

        # Add coordinate axes (x=red, y=green, z=blue)
        self.x_axis = self.create_axis([1, 0, 0], color=(1, 0, 0, 1))  # Red
        self.y_axis = self.create_axis([0, 1, 0], color=(0, 1, 0, 1))  # Green
        self.z_axis = self.create_axis([0, 0, 1], color=(0, 0, 1, 1))  # Blue

        self.view.addItem(self.x_axis)
        self.view.addItem(self.y_axis)
        self.view.addItem(self.z_axis)

        layout.addWidget(self.view)
        self.setLayout(layout)

    def create_axis(self, direction, length=1.5, color=(1, 1, 1, 1)):
        """Creates a single GL line item in given direction"""
        start = np.array([0, 0, 0])
        end = np.array(direction) * length
        pts = np.vstack([start, end])
        plt = gl.GLLinePlotItem(pos=pts, color=color, width=2, antialias=True)
        return plt

    def update_imu_data(self, accel, gyro, orientation_rpy):
        # Update labels
        self.accel_label.setText(f"Accel: x: {accel[0]:.2f}, y: {accel[1]:.2f}, z: {accel[2]:.2f}")
        self.gyro_label.setText(f"Gyro : x: {gyro[0]:.2f}, y: {gyro[1]:.2f}, z: {gyro[2]:.2f}")

        # Update 3D orientation
        yaw, pitch, roll = (orientation_rpy)
        self.update_orientation(yaw, pitch, roll)

    def update_orientation(self, yaw, pitch, roll):
        """Rotate axes to represent current orientation"""
        Rz = np.array([[np.cos(yaw), -np.sin(yaw), 0],
                       [np.sin(yaw),  np.cos(yaw), 0],
                       [0, 0, 1]])
        Ry = np.array([[np.cos(pitch), 0, np.sin(pitch)],
                       [0, 1, 0],
                       [-np.sin(pitch), 0, np.cos(pitch)]])
        Rx = np.array([[1, 0, 0],
                       [0, np.cos(roll), -np.sin(roll)],
                       [0, np.sin(roll), np.cos(roll)]])

        R = Rz @ Ry @ Rx

        # Apply to each axis line
        self.x_axis.setData(pos=np.array([[0, 0, 0], R[:, 0] * 1.5]))
        self.y_axis.setData(pos=np.array([[0, 0, 0], R[:, 1] * 1.5]))
        self.z_axis.setData(pos=np.array([[0, 0, 0], R[:, 2] * 1.5]))
