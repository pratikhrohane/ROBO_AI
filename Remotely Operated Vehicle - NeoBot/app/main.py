# main.py

from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QVBoxLayout, QHBoxLayout,
    QFrame, QSizePolicy, QSplitter
)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont
from panels.sensor_panel import SensorPanel
from panels.log_panel import LogPanel
from panels.imu_panel import IMUPanel
from panels.camera_panel import CameraPanel
from panels.radar_panel import RadarPanel
from panels.controller_panel import ControllerPanel

from mqtt_client import MQTTClient


import sys


class Card(QFrame):
    def __init__(self, title):
        super().__init__()
        self.setStyleSheet("""
            QFrame {
                background-color: #0F1C2E;
                border-radius: 16px;
                padding: 0px;
            }
            QLabel {
                color: white;
            }
        """)
        layout = QVBoxLayout()
        self.title = QLabel(title)
        self.title.setFont(QFont("Arial", 10, QFont.Bold))
        self.title.setStyleSheet("background-color: #1C2A3A; padding: 5px; border-radius: 10px; color: white;")
        layout.addWidget(self.title)
        layout.addStretch()
        self.setLayout(layout)

class RobotControlUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Robot Control UI")
        self.setGeometry(100, 100, 900, 600)
        self.setWindowFlags(Qt.Window | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint)
        self.setStyleSheet("background-color: #102A43;")

        # === MQTT ===
        self.mqtt_client = MQTTClient()
        self.mqtt_client.message_received.connect(self.handle_mqtt_message)

        # === IMU Data ===
        self.imu_accel = [0.0, 0.0, 0.0]
        self.imu_gyro = [0.0, 0.0, 0.0]

        # === LEFT PANEL ===
        left_panel = QWidget()
        left_layout = QVBoxLayout()
        left_layout.setSpacing(10)

        # Sensor Status
        sensor_card = Card("Sensor Status")
        self.sensor_panel = SensorPanel(temp_val=0, humidity_val=0, air_quality_val="Poor", light_val="Day")
        sensor_card.layout().addWidget(self.sensor_panel)

        # IMU + CAM
        imu_camera_splitter = QSplitter(Qt.Horizontal)
        imu_card = Card("IMU")
        cam_card = Card("CAM")
        imu_camera_splitter.addWidget(imu_card)
        imu_camera_splitter.addWidget(cam_card)
        imu_camera_splitter.setSizes([1, 1])

        left_layout.addWidget(sensor_card)
        left_layout.addWidget(imu_camera_splitter)
        left_panel.setLayout(left_layout)

        # IMU
        self.imu_panel = IMUPanel()
        imu_card.layout().addWidget(self.imu_panel)
        self.imu_panel.update_imu_data(
            accel=self.imu_accel,
            gyro=self.imu_gyro,
            orientation_rpy=self.imu_gyro
        )

        # CAM
        cam_panel = CameraPanel()
        cam_card.layout().addWidget(cam_panel)

        # === RIGHT PANEL ===
        right_panel = QWidget()
        right_layout = QVBoxLayout()
        right_layout.setSpacing(10)

        radar_card = Card("Radar View")
        controller_card = Card("Controller")

        right_layout.addWidget(radar_card)
        right_layout.addWidget(controller_card)
        right_panel.setLayout(right_layout)

        # Radar
        radar_panel = RadarPanel()
        radar_card.layout().addWidget(radar_panel)

        # Controller
        self.controller_panel = ControllerPanel(command_callback=self.send_command)
        controller_card.layout().addWidget(self.controller_panel)

        # === LOG PANEL (Full Width Bottom) ===
        log_card = Card("Log Data")
        self.log_panel = LogPanel()
        log_card.layout().addWidget(self.log_panel)

        # === MAIN SPLIT VIEW ===
        main_content_layout = QHBoxLayout()
        main_content_layout.addWidget(left_panel)
        main_content_layout.addWidget(right_panel)

        # === MAIN LAYOUT ===
        main_layout = QVBoxLayout(self)
        main_layout.addLayout(main_content_layout)
        main_layout.addWidget(log_card)

        # Size policies
        sensor_card.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        log_card.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        imu_camera_splitter.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        radar_card.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        controller_card.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)


    def handle_mqtt_message(self, topic, payload):
        # print(f"MQTT → {topic}: {payload}")
        self.log_panel.add_log(f"[{topic}] {payload}")

        try:
            data = float(payload) if "." in payload else int(payload)
        except:
            data = payload  # in case it's a string like "Poor", "Day", etc.

        # === SENSOR PANEL UPDATES ===
        if topic == "roboai/neobot/sensor/dht/temperature":
            self.sensor_panel.set_temperature(data)
        elif topic == "roboai/neobot/sensor/dht/humidity":
            self.sensor_panel.set_humidity(data)
        elif topic == "roboai/neobot/sensor/mq2":
            self.sensor_panel.set_air_quality(data)
        elif topic == "roboai/neobot/sensor/ldr":
            self.sensor_panel.set_light(data)

        if topic == "roboai/neobot/sensor/imu/accel":
            try:
                x, y, z = map(float, payload.split(","))
                self.imu_accel = [x, y, z]
            except:
                return
        elif topic == "roboai/neobot/sensor/imu/gyro":
            try:
                x, y, z = map(float, payload.split(","))
                self.imu_gyro = [x, y, z]
            except:
                return
        self.imu_panel.update_imu_data(
            accel=self.imu_accel,
            gyro=self.imu_gyro,
            orientation_rpy=self.imu_gyro
        )
    
    def send_command(self, cmd):
        self.mqtt_client.publish("roboai/neobot/command", cmd)
        self.log_panel.add_log(f"[CMD] {cmd}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = RobotControlUI()
    window.show()
    sys.exit(app.exec_())
