import pygame
import sys
import serial

# Initialize Pygame
pygame.init()

# Set up the joystick
pygame.joystick.init()
if pygame.joystick.get_count() == 0:
    print("No joystick/gamepad detected. Please connect a game controller.")
    sys.exit(1)

joystick = pygame.joystick.Joystick(0)
joystick.init()

# Set up the serial connection
ser1 = serial.Serial('COM5', 115200)  # Replace 'COM5' with the appropriate port for your Arduino 
ser2 = serial.Serial('COM9', 115200)  # Replace 'COM5' with the appropriate port for your Arduino 

def map_value(value, in_min, in_max, out_min, out_max):
    # Map a value from one range to another range
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def apply_deadzone(value, deadzone, center):
    # Apply a deadzone to the value with a specified center
    if center - deadzone <= value <= center + deadzone:
        return center
    return value

def main():
    # Set the deadzone threshold to 15 units
    deadzone = 15

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        # Get analog stick data
        left_x_axis = joystick.get_axis(0)
        left_y_axis = joystick.get_axis(1)
        right_x_axis = joystick.get_axis(2)
        right_y_axis = joystick.get_axis(3)

        # Map analog stick data to a range appropriate for your application
        # In this example, we map the values from -1 to 1 to 0 to 255
        left_x_mapped = int(map_value(left_x_axis, -1, 1, 0, 255))
        left_y_mapped = int(map_value(left_y_axis, -1, 1, 0, 255))
        right_x_mapped = int(map_value(right_x_axis, -1, 1, 0, 255))
        right_y_mapped = int(map_value(right_y_axis, -1, 1, 0, 255))

        # Apply deadzone to mapped values with center at 128
        left_x_mapped = apply_deadzone(left_x_mapped, deadzone, 128)
        left_y_mapped = apply_deadzone(left_y_mapped, deadzone, 128)
        right_x_mapped = apply_deadzone(right_x_mapped, deadzone, 128)
        right_y_mapped = apply_deadzone(right_y_mapped, deadzone, 128)

        #gets the state of the right trigger
        rightTrigStatus = joystick.get_button(10)

        #gets the state of the horizontal D-PAD buttons
        if joystick.get_button(14) == True: #move AX4 positive
            xDpadStatus = 1
        elif joystick.get_button(13) == True: #move AX4 negative
            xDpadStatus = 2
        else: #keep AX4 in its current position
            xDpadStatus = 0
        
        #gets the state of the vertical D-PAD buttons
        if joystick.get_button(11) == True: #move AX5 positive
            yDpadStatus = 1
        elif joystick.get_button(12) == True: #move AX5 negative
            yDpadStatus = 2
        else: #keep AX4 in its current position
            yDpadStatus = 0

        # Construct the data string to send to Arduino
        data_to_send1 = f"{left_x_mapped},{left_y_mapped},{right_y_mapped}\n" #i commented this out to test the jaw motor
        data_to_send2 = f"{rightTrigStatus},{xDpadStatus},{yDpadStatus}\n"
        # Send data to Arduino over the serial port 
        ser1.write(data_to_send1.encode())
        ser2.write(data_to_send2.encode())
        print(data_to_send1 + data_to_send2)

if __name__ == "__main__":
    main()
