import serial
import asyncio
import websockets
import json

# ---- CONFIG: change this to your Arduino's port ----
SERIAL_PORT = "COM18"   # <-- update this to match your port
BAUD_RATE = 9600

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

connected_clients = set()

async def handle_client(websocket):
    connected_clients.add(websocket)
    print("Game connected.")
    try:
        async for message in websocket:
            pass
    finally:
        connected_clients.remove(websocket)
        print("Game disconnected.")

async def read_serial_and_broadcast():
    while True:
        try:
            line = ser.readline().decode("utf-8").strip()
            if line and "," in line:
                parts = line.split(",")
                if len(parts) == 4:
                    # sketch sends x,y,z,proximity
                    x_str, y_str, z_str, prox_str = parts
                    data = {
                        "x": float(x_str),
                        "y": float(y_str),
                        "z": float(z_str),
                        "proximity": int(prox_str)
                    }
                    message = json.dumps(data)
                    for client in list(connected_clients):
                        try:
                            await client.send(message)
                        except:
                            pass
        except Exception as e:
            print("Error reading serial:", e)

        await asyncio.sleep(0.01)

async def main():
    server = await websockets.serve(handle_client, "localhost", 8765)
    print("WebSocket server running on ws://localhost:8765")
    await read_serial_and_broadcast()

asyncio.run(main())
