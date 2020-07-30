import inputs
import serial


def translate_int(value, left_min, left_max, right_min, right_max):
    # Figure out how 'wide' each range is
    left_span = left_max - left_min
    right_span = right_max - right_min

    # Convert the left range into a 0-1 range (float)
    value_scaled = float(value - left_min) / float(left_span)

    # Convert the 0-1 range into a value in the right range.
    return int(right_min + (value_scaled * right_span))


pads = inputs.devices.gamepads

if len(pads) == 0:
    raise Exception("Couldn't find any Gamepads!")

maxX = 0
minX = 0

deadzone = 3500
max_out = 255

i = 0

axes = ['ABS_X', 'ABS_Y', 'ABS_RX', 'ABS_RY']
axes_values = [0, 0, 0, 0]

while True:
    events = inputs.get_gamepad()
    for event in events:

            i = 0
            if event.code == axes[i] and event.state >= deadzone:
                axes_values[i] = translate_int(event.state, deadzone, 32767, 0, max_out)
            elif event.code == axes[i] and event.state <= -deadzone:
                axes_values[i] = translate_int(event.state, -32767, deadzone, -max_out, 0)

            i = 1
            if event.code == axes[i] and event.state >= deadzone:
                axes_values[i] = translate_int(event.state, deadzone, 32767, 0, max_out)
            elif event.code == axes[i] and event.state <= -deadzone:
                axes_values[i] = translate_int(event.state, -32767, deadzone, -max_out, 0)

            i = 2
            if event.code == axes[i] and event.state >= deadzone:
                axes_values[i] = translate_int(event.state, deadzone, 32767, 0, max_out)
            elif event.code == axes[i] and event.state <= -deadzone:
                axes_values[i] = translate_int(event.state, -32767, deadzone, -max_out, 0)

            i = 3
            if event.code == axes[i] and event.state >= deadzone:
                axes_values[i] = translate_int(event.state, deadzone, 32767, 0, max_out)
            elif event.code == axes[i] and event.state <= -deadzone:
                axes_values[i] = translate_int(event.state, -32767, deadzone, -max_out, 0)

            print(axes_values)
    # if event.state > maxX:
        #     maxX = event.state
        #
        # elif event.state < minX:
        #     minX = event.state
        #
        # print("Current Max: " + str(maxX))
        # print("Current Min: " + str(minX))
