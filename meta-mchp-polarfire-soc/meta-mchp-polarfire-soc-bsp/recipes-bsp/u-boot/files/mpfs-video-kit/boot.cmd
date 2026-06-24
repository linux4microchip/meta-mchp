setenv fitconf conf-mpfs-video-kit.dtb
load mmc 0:${distro_bootpart} ${scriptaddr} fitImage
bootm start ${scriptaddr}#${fitconf}#conf-mpfs_video_cpu_opp.dtbo
bootm loados ${scriptaddr};
# Try to load a ramdisk if available inside fitImage
bootm ramdisk;
bootm prep;
run design_overlays;
bootm go;
