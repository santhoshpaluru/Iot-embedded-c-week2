# IoT & C Embedded Programming Internship - Week 2

Sensors and communication (Arduino-style C, Arduino Uno pinouts).

## Contents
| Folder | Task |
|---|---|
| `01_lm35_adc_serial` | LM35 temperature read through ADC, printed on Serial Monitor |
| `02_ultrasonic_distance` | HC-SR04 distance in cm |
| `03_i2c_master`, `03_i2c_slave` | I2C between two boards (master sends LED command, reads slave ADC value) |
| `04_uart_timestamp_logger` | UART logger with timestamped readings |
| `mini_project_multisensor_logger` | Temperature + distance + light logger with buzzer alerts |

## Wiring
- LM35: pin 1 to 5V, pin 2 to A0, pin 3 to GND
- HC-SR04: VCC 5V, GND, TRIG pin 9, ECHO pin 10
- I2C: A4 to A4 (SDA), A5 to A5 (SCL), GND to GND between both boards. Upload the slave sketch to one board and the master to the other
- LDR: one leg to 5V, other leg to A1 and to GND through a 10k resistor
- Buzzer: pin 8 to GND

Serial Monitor baud rate: 9600.

## Author
Your Name - Skill Nexis Internship
