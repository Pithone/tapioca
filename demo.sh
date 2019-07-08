cd ~/tapioca/rpi-rgb-led-matrix/examples-api-use

# Image demo
sudo ./demo --led-cols=64 --led-rows=32 --led-chain=2 --led-pixel-mapper="U-mapper;Rotate:90" --led-pwm-lsb-nanoseconds 130 --led-scan-mode=1 -D 1 runtext.ppm

# Text demo
sudo ./scrolling-text-example --led-cols=64 --led-rows=32 --led-chain=2 --led-pixel-mapper="U-pper;Rotate:90" --led-pwm-lsb-nanoseconds 130 --led-scan-mode=1 "Viva la figa" -f ../fonts/10x20.bdf -C 255,0,0

popd
