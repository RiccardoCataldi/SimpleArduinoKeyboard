import mido
import serial

def print_message(msg):
    print("Received MIDI message: ", msg)
    if msg.type == "note_on":
        ser.write(f"{msg.note}\n".encode())
    elif msg.type == "note_off":
        ser.write(f"note_off {msg.note}\n".encode()) 

ser = serial.Serial(port='COM3', baudrate=115200, timeout=.1) 

input_port_name = mido.get_input_names()[0]

while True:
    try:
        with mido.open_input(input_port_name) as inport:
            for msg in inport:
                print_message(msg)
                print(msg.type)
    except KeyboardInterrupt:
        print("KeyboardInterrupt")
        ser.close()
        break
