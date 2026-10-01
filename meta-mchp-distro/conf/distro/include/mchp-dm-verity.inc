# dm-verity: cryptographically verify rootfs integrity at runtime
INITRAMFS_IMAGE = "dm-verity-image-initramfs"
DM_VERITY_IMAGE_TYPE ?= "ext4"
IMAGE_CLASSES += "dm-verity-img"
INITRAMFS_IMAGE_BUNDLE = "1"
EXTRA_IMAGE_FEATURES += "read-only-rootfs"

# Build linux-yocto-fitimage from openembedded-core by default
# fpga family uses linux-yocto-fitimage and
# mpu family uses dt-overlay-mchp
DM_VERITY_FIT_RECIPE ?= "linux-yocto-fitimage"

# WIC image depends on fitimage containing the verity root hash
do_image_wic[depends] += "${DM_VERITY_FIT_RECIPE}:do_deploy"
MACHINE_ESSENTIAL_EXTRA_RDEPENDS:remove = "${DM_VERITY_FIT_RECIPE}"

DISTRO_FEATURES:append = " security"

# Disable auto-resize since rootfs is read only
MCHP_FEATURES:remove = "mchp-autoresize"

# overlayfs-etc provides a writable /etc on top of the read-only rootfs
IMAGE_FEATURES += "overlayfs-etc"
IMAGE_FEATURES:remove = "package-management"
OVERLAYFS_ETC_MOUNT_POINT ?= "/mnt"
OVERLAYFS_ETC_FSTYPE ?= "ext4"
OVERLAYFS_ETC_DEVICE ?= "/dev/mmcblk0p4"
OVERLAYFS_ETC_MOUNT_OPTIONS ?= "defaults"
OVERLAYFS_ETC_CREATE_MOUNT_DIRS = "0"
