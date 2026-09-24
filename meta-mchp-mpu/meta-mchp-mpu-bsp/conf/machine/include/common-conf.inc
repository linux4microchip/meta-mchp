# Common to all machines in mpu
MACHINE_FEATURES += " apm alsa ext2 ext3 usbhost usbgadget screen touchscreen"

# Add a sdmmc feature to identify mpu machines with SD or eMMC
MACHINE_FEATURES:append = "${@' sdmmc' if '-sd' in d.getVar('MACHINE') or '-emmc' in d.getVar('MACHINE') else ''}"
MACHINEOVERRIDES:append = "${@bb.utils.contains('MACHINE_FEATURES', 'sdmmc', ':autoresize', '', d)}"

# MPU-only authenticated boot configuration, mirroring mpfs-auth.inc and
# pic64gx-auth.inc for the other families.
require ${@bb.utils.contains('DISTRO_FEATURES', 'mchp-auth', 'mpu-auth.inc', '', d)}

# Add bootloaders to the images of every machine
EXTRA_IMAGEDEPENDS += " at91bootstrap virtual/bootloader"

# When mchp-auth (for secureboot) distro feauture is enabled as part of
# secureboot, include the signed+encrypted u-boot.cip instead of u-boot.bin.
# at91bootstrap authenticates u-boot.cip
IMAGE_BOOT_FILES:append:mchp-auth = " u-boot.cip"
IMAGE_BOOT_FILES:remove:mchp-auth = "u-boot.bin"

# The ROM code authenticates at91bootstrap as boot.cip, so that replaces
# BOOT.BIN in the image.
IMAGE_BOOT_FILES:append:mchp-auth = " boot.cip"
IMAGE_BOOT_FILES:remove:mchp-auth = "BOOT.BIN"

# Chip type to be used with secure sam-ba cipher package. These are the names the
# package registers for its image formats, so the value has to be one of them.
# Keyed on the SoC family overrides the machine confs actually set (see
# MACHINEOVERRIDES there) rather than on the bare SoC name, which matches no
# machine. Left empty for families with no secure sam-ba support, which
# at91bootstrap turns into a bbfatal rather than an unsigned boot.
MCHP_SECURE_CHIP_TYPE ?= ""
MCHP_SECURE_CHIP_TYPE:sam9x60ek = "sam9x60"
MCHP_SECURE_CHIP_TYPE:sam9x60_curiosity = "sam9x60"
MCHP_SECURE_CHIP_TYPE:sam9x75eb = "sam9x70"
MCHP_SECURE_CHIP_TYPE:sam9x75_curiosity = "sam9x70"
MCHP_SECURE_CHIP_TYPE:sam9x75_curiosity_pro = "sam9x70"
MCHP_SECURE_CHIP_TYPE:sama5d2_xplained = "sama5d2x"
MCHP_SECURE_CHIP_TYPE:sama5d2_icp = "sama5d2x"
MCHP_SECURE_CHIP_TYPE:sama5d2_ptc_ek = "sama5d2x"
MCHP_SECURE_CHIP_TYPE:sama5d27_som1_ek = "sama5d2x"
MCHP_SECURE_CHIP_TYPE:sama5d27_wlsom1_ek = "sama5d2x"
MCHP_SECURE_CHIP_TYPE:sama5d29_curiosity = "sama5d2x"
MCHP_SECURE_CHIP_TYPE:sama5d3_xplained = "sama5d3x"
MCHP_SECURE_CHIP_TYPE:sama5d4_xplained = "sama5d4x"
MCHP_SECURE_CHIP_TYPE:sama7g5ek = "sama7g5"
MCHP_SECURE_CHIP_TYPE:sama7d65 = "sama7d65"

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
