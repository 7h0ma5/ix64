if [ "$DISPLAY" == "" ]; then
  if [ "$1" == "debug" ]; then
    qemu-system-x86_64 -cpu core2duo -vnc :1 -S -s -cdrom os.iso
  else
    qemu-system-x86_64 -cpu core2duo -vnc :1 -cdrom os.iso
  fi
else
  if [ "$1" == "debug" ]; then
    qemu-system-x86_64 -cpu core2duo -S -s -cdrom os.iso
  else
    qemu-system-x86_64 -cpu core2duo -cdrom os.iso
  fi
fi