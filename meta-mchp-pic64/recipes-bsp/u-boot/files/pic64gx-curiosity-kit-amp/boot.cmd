setenv fdt_high 0xbfffffff
setenv initrd_high 0xbfffffff

load mmc 0:${distro_bootpart} ${scriptaddr} fitImage
bootm start ${scriptaddr}#conf-pic64gx-curiosity-kit.dtb#conf-pic64gx_curiosity_kit_amp.dtbo;
bootm loados ${scriptaddr};
# Try to load a ramdisk if available inside fitImage
bootm ramdisk;
bootm prep;
bootm go;
