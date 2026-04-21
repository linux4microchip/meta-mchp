load mmc 0:${distro_bootpart} ${scriptaddr} fitImage
bootm start ${scriptaddr};
bootm loados ${scriptaddr};
# Try to load a ramdisk if available inside fitImage
bootm ramdisk;
bootm prep;
bootm go;
