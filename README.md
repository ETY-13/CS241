# CS241

**The Problem:**\
My goal is to create a toy car that can move by itself, avoiding obstacles and places where it will get stuck. The car is equipped with an ultrasonic sensor that can detect obstacles in front of the car or on the left or right side. Ideally, when there is an obstacle in front of the car, it should stop, use the ultrasonic sensor to look right and left, and turn in the direction that has no obstacle. With the ultrasonic sensor as the car's eyes, it should be able to move around, randomly, without getting stuck.

**The approach:**\
The approach that I take to solve the problem is to make a car out of cardboard cutouts. I use three wheels to drive the car; the front wheel is a cartwheel that can rotate 360 degrees, while the back wheels are two bigger wheels that are attached to TT motors. The motors are controlled by an L293D motor controller. A servo is used to rotate the ultrasonic sensor to look left (0 degrees), forward (95 degrees), or to the right (180 degrees), which is sitting at the front of the car. Everything runs on an Arduino Uno and is powered by a 9 volts battery. The pictures below show what the car looks like from the top, front, and bottom.\

![font](https://github.com/ETY-13/CS241/blob/main/car_images/top.jpg)

Upon starting the car (attaching a battery to the car), the ultrasonic check if there is any obstacle in front of the car; if not, it drives forward. If there is an obstacle, such as a wall, in front of the car, it will turn right (by rotating the servo 180 degrees) and check if there is any obstacle on the right and turn right if there is no obstacle, or check it left side. If obstacles exist on the front, right, and left side of the car, it will back up and choose to turn left or right randomly.
A loop counter is used to keep track of how many times the car had moved forward without turning left or right or backing up. Once the counter is greater than five, the program checks whether the car is moving closer to an obstacle; if it did not, the car is probably stuck and is forced to move backward and turn right or left randomly.
The program above loops endlessly as long as the car is alive, allowing it to move randomly and avoid getting stuck. The program is not perfect, and also is the sensor; therefore, the car does not avoid obstacles every time and can still be stuck until it backs up to save itself.  The Arduino code for the project is below.
