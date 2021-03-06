# Lydia ![Version 0.1](https://img.shields.io/badge/Version-0.1-green.svg)


[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)
![Built with love](https://img.shields.io/badge/built%20with-%E2%9D%A4-FF8080.svg)

Lydia is a thoughtfully created, RESTfully controlled quadruped robot. She's fun to play with and easy to build.

Lydia is made to be simple and affordable. She's 100% 3D printable and is powered by an ESP8266 so any device with WiFi can be used as a controller.

If you like or are using this project, please give it a :star: for motivation :)

![Picture of Lydia](/lydia.jpg)

## API Docs

Lydia is controlled by sending her HTTP request. This means that you can simply open up a web browser or use `curl` to start issuing her commands.

#### Walk Request

Issue walk commands to Lydia by making a post request to `/walk/`.

Arguments:

```
direction: the direction to move Lydia
  - forward
  - backward
  - left
  - right
duration: the amount of ms to move Lydia
```

Example walk request:

```
POST /walk?direction=forward&duration=3000
```

Responds with `200` upon success.

#### Turn Request

Lydia may be rotated by making a post request to `/turn/`.

Arguments:

```
direction: the direction to rotate Lydia
  - clockwise
  - counter
duration: the amount of ms to rotate Lydia
```

Example Turn Request:

```
POST /turn?direction=clockwise&duration=3000
```

Responds with `200` upon success.

#### API Info

You may request API info by making a GET request to Lydia's webroot:

```
GET /
```

This will respond with a JSON object describing the other endpoints.

## Project Setup

Instructions how to flash and program ESP8266 can be found [here](/arduino/README.md). More instructions will be released with time, including how to print everything and what parts to order.

## Project Roadmap

- Implement webserver API (in-progress).
- Update documentation to be beginner friendly.
- Write client to contact with API.

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

- [ESP8266 Arduino Port](https://github.com/esp8266/Arduino) github.
- [ESP8266.com Forums](http://www.esp8266.com/)
- [ESP8266.com Wiki](http://www.esp8266.com/wiki)
- [NodeMCU docs](http://nodemcu.readthedocs.io/en/dev/)
- [NodeMCU Builds](http://nodemcu-build.com/), builds custom firmware in the cloud.

## License

- MIT, see [LICENSE](/LICENSE) for more details.
