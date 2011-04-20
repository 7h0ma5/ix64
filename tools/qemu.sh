if [ -n "$DISPLAY" ]; then
  qemu-system-x86_64 -cdrom os.iso
else
  qemu-system-x86_64 -vnc :1 -cdrom os.iso
fi