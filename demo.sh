cd ~/tapioca/rpi-rgb-led-matrix/examples-api-use

# Reset panels
python3 resetmatrix.py

# Image demo
sudo ./demo --led-rows=32 --led-cols=64 --led-chain=2 --led-pixel-mapper="U-mapper;Rotate:90" --led-pwm-bits=11 --led-show-refresh --led-slowdown-gpio=0 --led-pwm-lsb-nanoseconds=100 --led-brightness=50 -D 4

# Text demo
sudo ./scrolling-text-example --led-cols=64 --led-rows=32 --led-chain=2 --led-pixel-mapper="U-pper;Rotate:90" --led-pwm-lsb-nanoseconds 130 --led-scan-mode=1 "Viva la figa" -f ../fonts/10x20.bdf -C 255,0,0

popd
