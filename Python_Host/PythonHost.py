import inputs
import serial

pads = inputs.devices.gamepads

if len(pads) == 0:
    raise Exception("Couldn't find any Gamepads!")

maxX = 0
minX = 0

max_in = 32768
deadzone_in = 3500

max_out = 255
deadzone_out = 0

# rounding = 0

i = 0

axes = ['ABS_X', 'ABS_Y', 'ABS_RX', 'ABS_RY']
axes_values = [0, 0, 0, 0]


def translate(value, left_min, left_max, right_min, right_max):
    # Figure out how 'wide' each range is
    left_span = left_max - left_min
    right_span = right_max - right_min

    # Convert the left range into a 0-1 range (float)
    value_scaled = float(value - left_min) / float(left_span)

    # Convert the 0-1 range into a value in the right range.
    return round(right_min + (value_scaled * right_span))


while True:
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
            i += 1

    print(axes_values)