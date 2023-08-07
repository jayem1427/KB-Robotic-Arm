import pygame

# Initialize Pygame
pygame.init()

# Initialize the controller
controller = pygame.joystick.Joystick(0)
controller.init()

# Wait for the controller to be initialized
pygame.time.wait(1000)

# Main loop to print button indices
while True:
    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONDOWN:
            # Print the button index when pressed
            for i in range(controller.get_numbuttons()):
                if controller.get_button(i):
                    print(f"Button {i} pressed")
