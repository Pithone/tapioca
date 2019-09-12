# Reset panels
#python3 resetmatrix.py

cd ~/tapioca/rpi-rgb-led-matrix/examples-api-use

# Clock
sudo ./clock --led-rows=32 --led-cols=64 --led-chain=2 --led-pixel-mapper="U-mapper;Rotate:90" --led-pwm-bits=11 --led-show-refresh --led-slowdown-gpio=0 --led-pwm-lsb-nanoseconds=100 --led-brightness=50 -f ~/tapioca/montserrat.bdf -q "    %H" -w "    %M" -e "    %S" -C "255,255,255"

popd
