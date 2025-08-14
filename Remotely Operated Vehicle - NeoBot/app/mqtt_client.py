# mqtt_client.py

from PyQt5.QtCore import QObject, pyqtSignal
import paho.mqtt.client as mqtt

class MQTTClient(QObject):
    message_received = pyqtSignal(str, str)  # topic, payload

    def __init__(self, broker_ip='broker.hivemq.com', port=1883):
        super().__init__()
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.client.connect(broker_ip, port)
        self.client.loop_start()

    def on_connect(self, client, userdata, flags, rc):
        print("Connected to MQTT Broker with result code " + str(rc))
        # Subscribe to all relevant sensor topics
        topics = [
            "roboai/neobot/sensor/dht/temperature",
            "roboai/neobot/sensor/dht/humidity",
            "roboai/neobot/sensor/mq2",
            "roboai/neobot/sensor/ldr",
            "roboai/neobot/sensor/imu/accel",
            "roboai/neobot/sensor/imu/gyro",
            "roboai/neobot/sensor/distance"
        ]
        for topic in topics:
            client.subscribe(topic)

    def on_message(self, client, userdata, msg):
        self.message_received.emit(msg.topic, msg.payload.decode())

    def publish(self, topic, message):
        self.client.publish(topic, message)
