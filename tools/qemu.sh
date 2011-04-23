if [ "$DISPLAY" == "" ]; then
  if [ "$2" == "debug" ]; then
    qemu-system-x86_64 -cpu core2duo -vnc :1 -S -s -cdrom "$1"
  else
    qemu-system-x86_64 -cpu core2duo -vnc :1 -cdrom "$1"
  fi
else
  if [ "$2" == "debug" ]; then
    qemu-system-x86_64 -cpu core2duo -S -s -cdrom "$1"
  else
    $(qemu-system-x86_64 -cpu core2duo -cdrom $1)
  fi
fi