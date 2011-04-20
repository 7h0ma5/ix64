mkisofs -graft-points -R -b boot/eltorito.img -no-emul-boot \
        -boot-load-size 4 -boot-info-table -o os.iso \
         boot/=boot/ boot/kernel.bin=kernel.bin