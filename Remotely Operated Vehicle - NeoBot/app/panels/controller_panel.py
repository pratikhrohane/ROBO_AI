# panels/controller_panel.py

from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QGridLayout
from PyQt5.QtCore import Qt, QPropertyAnimation, QRect
from PyQt5.QtGui import QFont

class ControllerPanel(QWidget):
    def __init__(self, command_callback=None):
        super().__init__()
        self.command_callback = command_callback  # Callback to send MQTT or update UI
        self.setStyleSheet("background-color: transparent;")
        layout = QVBoxLayout(self)

        self.grid = QGridLayout()
        self.grid.setSpacing(20)

        # Create emoji buttons
        self.btn_forward = self.create_button("🢁", "FWD")
        self.btn_left = self.create_button("🢀", "LFT")
        self.btn_right = self.create_button("🢂", "RHT")
        self.btn_backward = self.create_button("🢃", "BWD")
        self.btn_stop = self.create_button("◻", "STP")

        # D-pad layout with Stop in the center
        self.grid.addWidget(self.btn_forward, 0, 1, alignment=Qt.AlignCenter)
        self.grid.addWidget(self.btn_left, 1, 0, alignment=Qt.AlignCenter)
        self.grid.addWidget(self.btn_stop, 1, 1, alignment=Qt.AlignCenter)
        self.grid.addWidget(self.btn_right, 1, 2, alignment=Qt.AlignCenter)
        self.grid.addWidget(self.btn_backward, 2, 1, alignment=Qt.AlignCenter)

        layout.addLayout(self.grid)
        self.setLayout(layout)

    def create_button(self, icon, command):
        btn = QPushButton(icon)
        btn.setFixedSize(60, 60)
        btn.setFont(QFont("Arial", 24))
        btn.setStyleSheet("""
            QPushButton {
                background-color: #1C2A3A;
                color: white;
                border-radius: 30px;
                padding: 5px;
            }
            QPushButton:pressed {
                background-color: #0078d7;
            }
        """)

        btn.pressed.connect(lambda c=command: self.send_command(c))
        btn.released.connect(lambda: self.send_command("STP"))

        return btn

    def send_command(self, cmd):
        self.animate_button(self.sender())
        if self.command_callback:
            self.command_callback(cmd)

    def animate_button(self, button):
        animation = QPropertyAnimation(button, b"geometry")
        rect = button.geometry()
        animation.setDuration(100)
        animation.setStartValue(rect)
        animation.setKeyValueAt(0.5, QRect(rect.x() + 2, rect.y() + 2, rect.width() - 4, rect.height() - 4))
        animation.setEndValue(rect)
        animation.start()
