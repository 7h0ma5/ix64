mkisofs -graft-points -R -b boot/eltorito.img -no-emul-boot \
        -boot-load-size 4 -boot-info-table -o $2 \
         boot/=boot/ boot/kernel.bin=$1