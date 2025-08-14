import cv2
from PyQt5.QtWidgets import (
    QWidget, QLabel, QVBoxLayout, QComboBox, QHBoxLayout, QSizePolicy
)
from PyQt5.QtGui import QPixmap, QImage
from PyQt5.QtCore import QTimer, Qt
import time


class CameraPanel(QWidget):
    def __init__(self):
        super().__init__()

        self.setStyleSheet("background-color: #0F1C2E;")

        # --- Layout
        main_layout = QVBoxLayout()
        top_bar = QHBoxLayout()

        # --- Camera Selector
        self.camera_selector = QComboBox()
        self.camera_selector.addItems(["Camera 0", "Camera 1"])
        self.camera_selector.currentIndexChanged.connect(self.change_camera)
        self.camera_selector.setStyleSheet("""
            QComboBox {
                background-color: #1C2A3A;
                color: white;
                padding: 3px;
                border-radius: 5px;
            }
        """)

        # --- FPS Label
        self.fps_label = QLabel("FPS: 0")
        self.fps_label.setStyleSheet("color: grey; font-size: 10px; margin-left: 10px;")
        top_bar.addWidget(self.camera_selector)
        top_bar.addWidget(self.fps_label)
        top_bar.addStretch()

        # --- Camera Feed Display
        self.image_label = QLabel()
        self.image_label.setAlignment(Qt.AlignCenter)

        # Reduce camera size to 4/5 of card width and height
        self.image_label.setFixedSize(int(310), int(220))  # 4/5 of card approx
        self.image_label.setStyleSheet("border-radius: 10px;")

        # --- Add widgets
        main_layout.addLayout(top_bar)
        main_layout.addWidget(self.image_label)
        self.setLayout(main_layout)

        # --- Timer and Capture
        self.cap = cv2.VideoCapture(1)
        self.last_time = time.time()

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_frame)
        self.timer.start(30)

    def change_camera(self, index):
        self.cap.release()
        self.cap = cv2.VideoCapture(index)

    def update_frame(self):
        ret, frame = self.cap.read()
        if ret:
            frame = cv2.resize(frame, (self.image_label.width(), self.image_label.height()))
            rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            h, w, ch = rgb_image.shape
            bytes_per_line = ch * w
            qt_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)
            self.image_label.setPixmap(QPixmap.fromImage(qt_image))

            # FPS calculation
            current_time = time.time()
            fps = 1.0 / (current_time - self.last_time)
            self.fps_label.setText(f"FPS: {fps:.1f}")
            self.last_time = current_time

    def closeEvent(self, event):
        self.cap.release()
        event.accept()
