fdt addr ${fdtcontroladdr}
fdt get value board_compatible / compatible 1
setenv fitconf conf-microchip,rtpfs-dev-kit.dtb
load mmc 0:${distro_bootpart} ${scriptaddr} fitImage
bootm start ${scriptaddr}#${fitconf}
bootm loados ${scriptaddr};
# Try to load a ramdisk if available inside fitImage
bootm ramdisk;
bootm prep;
bootm go;