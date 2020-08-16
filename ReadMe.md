Curtain Robot
=============

Introduction
------------

This repository contains code, description, notes, and maybe eventually a
circuit diagram for a robot I am making so that I can open and close my curtains
using a remote control. A stretch goal of this project is to incorporate an
alarm clock so that the curtains will open and close on a user-defined schedule.

For this project I am cribbing heavily from [this youtube
tutorial](https://www.youtube.com/watch?v=JtYdPwO65WI) for the hardware setup,
although I have not (yet) stolen any of their code.

Components
----------

For this project I'm using an Elegoo Uno R3, an AX-1838HS IR receiver with a
38KHz universal IR remote control, and a Creality 3D 42-34 two-phase stepper
motor.

Logic
-----

Code lives [here](./motor_code/) and is adapted from the code that came
with the Elegoo Super Starter Kit module on controlling a stepper motor with an
IR remote. 

The goal is to have the curtains closing as long as the down arrow on the remote
is depressed and opening as long as the up arrow is depressed. Right now I am
approximating that by having the up or down arrow select the motor direction and
then having the motor increment 1/4 revolution every time a "repeat" signal is
detected. This is imperfect because there is a very brief pause every 1/4
revolution while the code loops, but it might be good enough if those pauses are
not noticeable in the actual curtain movement.

Videos
------

* [The first draft of the robot. Fixed amount of revolution per button
press.](https://www.youtube.com/watch?v=yPqz3ENg95E)

Rough Notes
-----------

### IR Remote Button codes

Left to right, top to bottom (like reading)

1. FFA25D
2. FF629D
3. FFE21D
4. FF22DD
5. FF02FD
6. FFC23D
7. FFE01F (up arrow)
8. FFA857
9. FF906F (down arrow)
10. FF6897
11. FF9867
12. FFB04F
13. FF30CF
14. FF18E7
15. FF7A85
16. FF10EF
17. FF38C7
18. FF5AA5
19. FF42BD
20. FF4AB5
21. FF52AD

repeat: FFFFFFFF
