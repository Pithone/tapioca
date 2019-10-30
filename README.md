# Tapioca

## Instructions

1. Install raspbian on the pi
    - Download latest raspbian installation from raspberrypi.org
        - `wget https://downloads.raspberrypi.org/raspbian_lite_latest`
    - Flash it to the sdcard
        - `unzip -p ./raspbian_lite_latest | sudo dd of=/dev/sdX bs=4M conv=fsync`
2. Put wireless network SSID and preshared key into `boot/wpa_supplicant.conf`
3. Copy all the `boot` directory into the raspberry pi boot partition
4. Power it up and connect to it via ssh
5. Update it and install git
    - `sudo touch /var/lib/dpkg/status && sudo apt update && sudo apt upgrade -y && sudo apt install git`
5. Clone this repo into the raspberry
    - `git clone --recurse-submodules git@github.com:Pithone/tapioca.git`
7. Compile demo software
    - `cd tapioca/submodules/rpi-rgb-led-matrix/examples-api-use`
    - `make`
    - `cd ../../..`
8. Run clock
    - `./scripts/clock.sh`

## Credits

The author of the resetmatrix.py script is [lucasParis](https://github.com/lucasParis)
