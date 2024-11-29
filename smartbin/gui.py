import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QProgressBar
import serial
    
class OperatorDashboard(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.serial = serial.Serial('COM3', 9600)

    def initUI(self):
        self.setWindowTitle("Operator Dashboard")
        layout = QVBoxLayout()

        self.temp_label = QLabel("Temperature: 0°C")
        self.level_label = QLabel("Waste Level: 0%")
        self.state_label = QLabel("State: Available")
        self.progress = QProgressBar()
        self.progress.setValue(0)

        self.empty_button = QPushButton("Empty Container")
        self.empty_button.clicked.connect(self.emptyContainer)
        self.restore_button = QPushButton("Restore System")
        self.restore_button.clicked.connect(self.restoreSystem)

        layout.addWidget(self.temp_label)
        layout.addWidget(self.level_label)
        layout.addWidget(self.state_label)
        layout.addWidget(self.progress)
        layout.addWidget(self.empty_button)
        layout.addWidget(self.restore_button)

        self.setLayout(layout)

    def emptyContainer(self):
        self.serial.write(b'EMPTY\n')

    def restoreSystem(self):
        self.serial.write(b'RESTORE\n')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = OperatorDashboard()
    ex.show()
    sys.exit(app.exec_())
