# Common to all machines in mpu
MACHINE_FEATURES += " apm alsa ext2 ext3 usbhost usbgadget screen touchscreen"

# Add a sdmmc feature to identify mpu machines with SD or eMMC
MACHINE_FEATURES:append = "${@' sdmmc' if '-sd' in d.getVar('MACHINE') or '-emmc' in d.getVar('MACHINE') else ''}"
MACHINEOVERRIDES:append = "${@bb.utils.contains('MACHINE_FEATURES', 'sdmmc', ':autoresize', '', d)}"

# Add bootloaders to the images of every machine
EXTRA_IMAGEDEPENDS += " at91bootstrap virtual/bootloader"

# MPU assembles its FIT with dt-overlay-mchp (mkimage -f <machine>.its), not with
# oe-core's linux-yocto-fitimage, which mchp-dm-verity.inc defaults to for the
# FPGA families. This is not merely a preference: kernel-fit-image.bbclass copies
# "linux.bin" out of the kernel deploy dir, and linux-mchp only deploys zImage,
# so linux-yocto-fitimage:do_compile fails on MPU.
DM_VERITY_FIT_RECIPE:mchp-dm-verity = "dt-overlay-mchp"

# dm-verity rootfs type for MPU. squashfs-xz keeps the rootfs (and so the A/B
# slots) around 4x smaller than ext4, which also means far fewer bytes for
# verity to hash in software on cores without crypto extensions. Rest of the
# families keep the ext4 default from mchp-dm-verity.inc.
DM_VERITY_IMAGE_TYPE:mchp-dm-verity = "squashfs-xz"
