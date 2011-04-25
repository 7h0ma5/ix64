if [ "$1" == "debug" ]; then
  $(qemu-system-x86_64 -cpu core2duo -S -s -kernel kernel.bin)
else
  $(qemu-system-x86_64 -cpu core2duo -kernel kernel.bin -monitor vc:1200x800)
fi