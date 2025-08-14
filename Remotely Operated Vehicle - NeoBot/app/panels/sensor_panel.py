from PyQt5.QtWidgets import QWidget, QLabel, QVBoxLayout, QHBoxLayout
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt


class SensorPanel(QWidget):
    def __init__(self, temp_val, humidity_val, air_quality_val, light_val):
        super().__init__()

        self.layout = QVBoxLayout()
        self.setLayout(self.layout)

        self.sensor_layout = QHBoxLayout()
        self.layout.addLayout(self.sensor_layout)

        # Create placeholders for each sensor block
        self.temp_widget = self.create_sensor_widget()
        self.humidity_widget = self.create_sensor_widget()
        self.air_quality_widget = self.create_sensor_widget()
        self.light_widget = self.create_sensor_widget()

        self.sensor_layout.addWidget(self.temp_widget)
        self.sensor_layout.addWidget(self.humidity_widget)
        self.sensor_layout.addWidget(self.air_quality_widget)
        self.sensor_layout.addWidget(self.light_widget)

        # Set initial values
        self.set_temperature(temp_val)
        self.set_humidity(humidity_val)
        self.set_air_quality(air_quality_val)
        self.set_light(light_val)

    def create_sensor_widget(self):
        widget = QWidget()
        layout = QVBoxLayout()
        layout.setAlignment(Qt.AlignCenter)

        icon_label = QLabel("❓")
        icon_label.setFont(QFont("Arial", 24))
        icon_label.setAlignment(Qt.AlignCenter)

        value_label = QLabel("0")
        value_label.setFont(QFont("Arial", 10))
        value_label.setStyleSheet("color: white;")
        value_label.setAlignment(Qt.AlignCenter)

        status_label = QLabel("Unknown")
        status_label.setFont(QFont("Arial", 9))
        status_label.setStyleSheet("color: grey;")
        status_label.setAlignment(Qt.AlignCenter)

        layout.addWidget(icon_label)
        layout.addWidget(value_label)
        layout.addWidget(status_label)

        widget.setLayout(layout)
        widget.icon_label = icon_label
        widget.value_label = value_label
        widget.status_label = status_label

        return widget

    def evaluate_sensor(self, sensor_type, value):
        try:
            val = float(value)
        except:
            val = value

        if sensor_type == "temperature":
            if val < 15:
                return "🥶", "Cold", "blue"
            elif 15 <= val < 30:
                return "🌤️", "Moderate", "green"
            else:
                return "🔥", "High", "red"

        elif sensor_type == "humidity":
            if val < 30:
                return "💨", "Dry", "yellow"
            elif 30 <= val <= 60:
                return "💧", "Moderate", "green"
            else:
                return "🌊", "High", "red"

        elif sensor_type == "air_quality":
            if val == "Good":
                return "🍃", "Good", "green"
            elif val == "Moderate":
                return "🌫️", "Moderate", "yellow"
            else:
                return "💨", "Poor", "red"

        elif sensor_type == "light":
            if val == 0:
                return "🌞", "Safe", "green"
            elif val == 1:
                return "🌙", "Risk", "blue"
            else:
                return "❓", "Unknown", "grey"

        return "❓", "Unknown", "grey"

    def update_sensor_widget(self, widget, icon, status, color, value):
        widget.icon_label.setText(icon)
        widget.value_label.setText(str(value))
        widget.status_label.setText(status)
        widget.status_label.setStyleSheet(f"color: {color};")

    # === External methods for each sensor update ===

    def set_temperature(self, temp):
        icon, status, color = self.evaluate_sensor("temperature", temp)
        self.update_sensor_widget(self.temp_widget, icon, status, color, f"{temp}°C")

    def set_humidity(self, humidity):
        icon, status, color = self.evaluate_sensor("humidity", humidity)
        self.update_sensor_widget(self.humidity_widget, icon, status, color, f"{humidity}%")

    def set_air_quality(self, quality):
        icon, status, color = self.evaluate_sensor("air_quality", quality)
        self.update_sensor_widget(self.air_quality_widget, icon, status, color, quality)

    def set_light(self, light_level):
        icon, status, color = self.evaluate_sensor("light", light_level)
        self.update_sensor_widget(self.light_widget, icon, status, color, light_level)
