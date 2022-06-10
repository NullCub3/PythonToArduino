import time
import logging
import inputs
import serial

print('Starting!')

serial_mode = False

pads = inputs.devices.gamepads

if len(pads) == 0:
    raise Exception("Couldn't find any Gamepads!")

# Serial Settings
ser = serial.Serial()
ser.baudrate = 230400
ser.port = 'COM7'
if serial_mode:
    ser.open()
transmit = bytes()
send_values = [0, 0]

tankDrive = True

# Axes config
axes = ['ABS_X', 'ABS_Y', 'ABS_RX', 'ABS_RY']  # Names of axes
axes_values = [0, 0, 0, 0]  # Stored axes values

max_in = 32768  # Maximum value of Gamepad
deadzone_in = 3500  # Minimum value of Gamepad

max_out = 255  # Maximum value of stored axes
deadzone_out = 0  # Minimum value of stored axes

rounding = 0  # How many decimal places to have


def translate(value, left_min, left_max, right_min, right_max):
    # Figure out how 'wide' each range is
    left_span = left_max - left_min
    right_span = right_max - right_min

    # Convert the left range into a 0-1 range (float)
    value_scaled = float(value - left_min) / float(left_span)

    # Convert the 0-1 range into a value in the right range.
    return round(right_min + (value_scaled * right_span), rounding)


def send(send_left, send_right):
    send_data = bytes(str(send_left) + ' ' + str(send_right) + '\n', 'utf-8')
    if serial_mode:
        ser.write(send_data)

    # Debug
    # print(send_left, send_right)
    print(send_data)


def get_gamepad():
    events = inputs.get_gamepad()
    for event in events:
        i = 0
        while i <= 3:
            if event.code == axes[i] and event.state >= deadzone_in:
                axes_values[i] = translate(event.state, deadzone_in, max_in, deadzone_out, max_out)
            elif event.code == axes[i] and event.state <= -deadzone_in:
                axes_values[i] = translate(event.state, -max_in, -deadzone_in, -max_out, -deadzone_out)
            elif event.code == axes[i] and deadzone_in >= event.state >= -deadzone_in:
                axes_values[i] = 0

            if event.code == axes[i] and rounding == 0:
                axes_values[i] = int(axes_values[i])
            i += 1


t = 0

print('Main Loop Running')
while True:
    print(str(t) + str(axes_values))
    t = t + 1
    if t >= 256:
        t = 0

    if tankDrive:
        send(axes_values[1], axes_values[3])
    get_gamepad()

