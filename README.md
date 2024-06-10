Ultrasonic Levitator

![schematic](https://github.com/PepeTheFroggie/Levitator/blob/main/Clipboard01.jpg)

Styro ball caught in the standing wave of 2 ultrasonic transducers. 
To move the ball i change the phase angle between the transducers. 
40khz, produced by a LGT8F328P. Using timer1 and timer3.

Video: https://www.youtube.com/watch?v=jtqRzI3yIdQ
Video showing signal to upper and lower transducer: https://youtu.be/_670pjSexg8

Controls: 
- 'F' an 'f' to change frequency
- 'P' an 'p' to change pwm intensity
- 'r' to move up
- 'z' to move down
- 't' to stop moving

The driver and mechanical ist two $3 aliexpress ultrasonic levitators. I use only the driver and transducer.
See modified schmatic. Connection points to LGT8F328P are Gnd, Ain, Bin.
Pins are Ain 1-PD1 Bin 2-PF1 and Ain 9-PB1 Bin 10-PB2

![schematic](https://github.com/PepeTheFroggie/Levitator/blob/main/schem.png)

