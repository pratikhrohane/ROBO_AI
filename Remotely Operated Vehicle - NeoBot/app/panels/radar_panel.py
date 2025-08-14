import sys
import math
import time
import random
from PyQt5.QtWidgets import (
    QApplication, QGraphicsView, QGraphicsScene, QGraphicsEllipseItem,
    QGraphicsTextItem, QVBoxLayout, QWidget
)
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QPen, QBrush, QColor, QPainter, QFont

class RadarPanel(QGraphicsView):
    def __init__(self):
        super().__init__()
        self.setRenderHint(QPainter.Antialiasing)
        self.setStyleSheet("background-color: black;")
        self.setFixedSize(300, 200)

        self.radius = 150
        self.max_range_cm = 200
        self.scene = QGraphicsScene(self)
        self.setScene(self.scene)

        self.radar_rings = []
        self.range_labels = []
        self.blips = []
        self.scan_line = None
        self.angle = 0

        self.draw_static_elements()

        self.timer = QTimer()
        self.timer.timeout.connect(self.update_radar)
        self.timer.start(50)

        self.cleanup_timer = QTimer()
        self.cleanup_timer.timeout.connect(self.cleanup_blips)
        self.cleanup_timer.start(500)

    def draw_static_elements(self):
        pen = QPen(QColor("green"))
        for r in range(50, self.max_range_cm + 1, 50):
            px = self.radius * (r / self.max_range_cm)
            ring = QGraphicsEllipseItem(self.radius - px, self.radius - px, 2 * px, px)
            ring.setPen(pen)
            self.scene.addItem(ring)
            self.radar_rings.append(ring)

            label = QGraphicsTextItem(f"{r} cm")
            label.setDefaultTextColor(Qt.white)
            label.setFont(QFont("Arial", 7))
            label.setPos(self.radius + 5, self.radius - px - 10)
            self.scene.addItem(label)
            self.range_labels.append(label)

    def update_radar(self):
        if self.scan_line:
            self.scene.removeItem(self.scan_line)

        angle_rad = math.radians(self.angle)
        x = self.radius + self.radius * math.cos(angle_rad)
        y = self.radius - self.radius * math.sin(angle_rad)
        self.scan_line = self.scene.addLine(self.radius, self.radius, x, y, QPen(Qt.green))

        now = time.time()
        for item, t in self.blips:
            if now - t < 2.0:
                item.setVisible(True)
            else:
                item.setVisible(False)

        if random.random() < 0.15:
            distance = random.randint(20, 180)
            self.add_blip(self.angle, distance)

        self.angle = (self.angle + 3) % 180

    def add_blip(self, angle_deg, distance_cm):
        angle_rad = math.radians(angle_deg)
        r = self.radius * (distance_cm / self.max_range_cm)
        x = self.radius + r * math.cos(angle_rad)
        y = self.radius - r * math.sin(angle_rad)

        dot = QGraphicsEllipseItem(x - 3, y - 3, 6, 6)
        dot.setPen(QPen(Qt.red))
        dot.setBrush(QBrush(Qt.red))
        self.scene.addItem(dot)
        self.blips.append((dot, time.time()))

    def cleanup_blips(self):
        now = time.time()
        self.blips = [(item, t) for item, t in self.blips if now - t < 2.0]


