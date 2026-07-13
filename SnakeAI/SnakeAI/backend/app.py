from flask import Flask, render_template
from flask_socketio import SocketIO
import serial
import threading

app = Flask(__name__)
socketio = SocketIO(app)

# Change COM17 if your Arduino is on another port
ser = serial.Serial("COM17", 115200, timeout=1)


def read_serial():
    while True:
        if ser.in_waiting:
            direction = ser.readline().decode().strip()

            if direction:
                print(direction)
                socketio.emit("direction", direction)


@app.route("/")
def home():
    return render_template("index.html")


threading.Thread(target=read_serial, daemon=True).start()

if __name__ == "__main__":
    socketio.run(app, debug=True, use_reloader=False)