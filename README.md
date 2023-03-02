# sound-controlled-switch

In this project, we use two Arduino development boards, which are called `master` and `slave`. 
The `master` Arduino process the sound that received by the micorphone module.
And the `slave` Arduino controls the serveo-motor to turn on (or turn off) the switch of some electronic device (e.g., a desk lamp)

## Code Organization
* `master_microphone/`
    * `microphone.ino`: code for the `master` Arduino
* `slave_motor/`
    * `servomotor.ino`: code for the `slave` Arduino

## Development Enviornment
We built this project by two `Arduino Uno` and serveral modules, namely `Bluetooth (HC-05)`, `microphone sound sensor (KY-037)` and the `servo-motor (SG90)`.

