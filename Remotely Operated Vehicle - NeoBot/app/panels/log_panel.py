from PyQt5.QtWidgets import QWidget, QVBoxLayout, QTextEdit

class LogPanel(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.init_ui()

    def init_ui(self):
        layout = QVBoxLayout()

        self.log_box = QTextEdit()
        self.log_box.setReadOnly(True)
        self.log_box.setStyleSheet("""
            background-color: #0b2740;
            color: #CCCCCC;
            border-radius: 10px;
            font-size: 11px;
        """)

        layout.addWidget(self.log_box)
        self.setLayout(layout)

        # Initial system message
        self.add_log("🟢 NeoBot Controller is Ready")

    def add_log(self, message):
        self.log_box.append(message)
