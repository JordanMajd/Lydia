# Arduino Processing Setup Instructions

## Setting up the IDE for the Feather Huzzah ESP8266

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


More info at [Adafruit](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)


## Uploading Code to ESP8266

1. Upload the [robot](/arduino/robot) sketch to device.


## Communicating with robot over Wifi
