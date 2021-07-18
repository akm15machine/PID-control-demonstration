# PID-control-demonstration
This is a very simple PID controller project for beginners.

## Objective
The objective is to keep a constant voltage across a capacitor very accurately over time.

## Schematic
![image](https://user-images.githubusercontent.com/55695557/126066228-95360d02-edce-488d-a9a1-c3aaf9a5c78d.png)
![PID control demo](https://user-images.githubusercontent.com/55695557/126080031-d82406d6-48a3-4992-bd8d-71abfd3f318a.png)


## Description
* Charging Network
  * There is a charging network for the 100uF capacitor from Pin 11
  * A 2.2k resistor is intentionally connected to cause a delay while charging (given by RC time constant) and also to limit the current from the GPIO.
  * An LED indicates the charging process of the capacitor
* Monitoring Network
  * The voltage across the capacitor is fed to Pin A0 of the Arduino for monitoring the voltage
  * A0 has an internal 10-bit (SAR) ADC
  * The value obtained from the ADC is mapped to a number 0 to 255 (256 levels) where 0 represents 0v and 255 represents 5.0v
  * Monitoring is used for the feedback and PID control
* Discharging Network (for testing)
  * There is a 100k Potentiometer which can be adjusted to different values in order to test the feedback
  * There is a discharging switch as well, which will be used to cause sudden large disturbance in the feedback network

## Flowchart
![image](https://user-images.githubusercontent.com/55695557/126067572-d879d8c7-7733-43a8-8fa0-3b3ef537fe61.png)

## Conclusion
This was just a simple demonstration of PID control system. However, it is possible to implement the same concept directly to set the temperature of a controlled heating system very accurately, where the temperature can be adjusted by changing the value of `setPoint` in the [code](PID_Control_Code/PID_Control_Code.ino) (definition at line 5).
