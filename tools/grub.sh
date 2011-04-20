grub-mkimage -p /boot -o tmp_core.img -O i386-pc biosdisk iso9660 multiboot normal ls cat help
cat /usr/lib/grub/i386-pc/cdboot.img tmp_core.img > boot/eltorito.img
rm -f tmp_core.img