# Quadruped

## About

A wifi controlled quadruped robot built using an ESP8266 controller.

The project can be programmed in Lua, AVR C or Arduino's Processing.

## Arduino Setup

> :warning: this will override any firmware currently on device :warning:

1. [Install CP2104 USB driver](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx).
1. [Install Arduino IDE](https://www.arduino.cc/en/Main/Software): `brew cask install arduino`.
1. Install the ESP8266 Board Package:
  - Update `Additional Boards Manager URL` in Preferences to: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
  - Use `Tools -> Board -> Board Manager...` to install the ESP8266 `v2.2` board definition.
  - Restart IDE.
  - From `Tools -> Board` dropdown, select `Generic ESP8266 Module`.
  - From `Tools -> CPU Fequency`, select `80 MHz`.
  - From `Tools -> Flash Size`, select `4M (3M SPIFFS)`.
  - From `Tools -> Upload Speed`, select `115200` baud or `921600` if you are feeling ballsy.
  - From `Tools -> Reset Method`, select `nodemcu`
  - Select the correct COM port.
1. Ensure setup looks like this:
```
Flash Mode "QIO"
Flash Frequency "40MHz"
Upload Using "Serial"
CPU Frequency "80 MHz"
Flash Size "4M"
Reset Method "nodemcu"
```
1. Upload the [test_config](/arduino/test_config) sketch to device, light should pulse in 500ms intervals.
1. Navigate to your `Arduino/libraries` directory and clone the [Adafruit-PWM-Servo-Driver-Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library) : `git clone git@github.com:adafruit/Adafruit-PWM-Servo-Driver-Library.git`
1. Upload the [robot](/arduino/robot) sketch to device.

More info at [Adafruit](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)

## Project Roadmap

- Research whether to use Arduino, Lua or AVR C.
- Assemble chassis
- Build firmware
- Write webserver API
- Write client to contact with API
- Write servo control

## Proposed Names

- Per-ungol (Evlish for half spider).

## Resources

Controllers:

- [Feather Huzzah: ESP 8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266?view=all), docs on the controller.
- [Feather PWM / Servo Sheild](https://www.adafruit.com/products/2928), servo controller product listing.
- [16 Channel PWM / Servo Shield](https://learn.adafruit.com/adafruit-16-channel-pwm-slash-servo-shield?view=all), docs on similar servo controller.

Chassis:

- [Allbot STL files](http://www.thingiverse.com/thing:1434665) for 3D printing.
- [Allbot documentation](http://manuals.velleman.eu/category.php) for parts list, assembly information.
- [Allbot Website](http://www.allbot.eu/)

Misc:

- [TowerPro SG99 Microservo docs](http://www.micropik.com/PDF/SG90Servo.pdf).

ESP8266 / NodeMCU:

- [ESP8266.com Forums](http://www.esp8266.com/)
- [ESP8266.com Wiki](http://www.esp8266.com/wiki)
- [NodeMCU docs](http://nodemcu.readthedocs.io/en/dev/)
- [NodeMCU Builds](http://nodemcu-build.com/), builds custom firmware in the cloud.

## Parts List

TODO

## License

See [LICENSE](/LICENSE).
