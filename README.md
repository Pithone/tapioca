# Tapioca

## Instructions

1. Install raspbian on the pi
    - Download latest raspbian installation from raspberrypi.org
        - `wget https://downloads.raspberrypi.org/raspbian_lite_latest`
    - Flash it to the sdcard
        - `unzip -p ./raspbian_lite_latest | sudo dd of=/dev/sdX bs=4M conv=fsync`
2. Put wireless network SSID and preshared key into `boot/wpa_supplicant.conf`
3. Put an empty file called `ssh` into the raspberry pi boot partition
4. Copy all the `boot` directory into the raspberry pi boot partition
5. Power it up and connect to it via ssh
6. Clone this repo into the raspberry
    - `git clone --recurse-submodules git@github.com:Pithone/tapioca.git`
7. Compile demo software
    - `cd tapioca/rpi-rgb-led-matrix/examples-api-use`
    - `make`
8. Run demo
    - `./demo.sh`
