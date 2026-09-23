# dm-verity: cryptographically verify rootfs integrity at runtime
INITRAMFS_IMAGE = "dm-verity-image-initramfs"
DM_VERITY_IMAGE_TYPE ?= "ext4"
IMAGE_CLASSES += "dm-verity-img"
INITRAMFS_IMAGE_BUNDLE = "1"
EXTRA_IMAGE_FEATURES += "read-only-rootfs"

# WIC image depends on fitimage containing the verity root hash
do_image_wic[depends] += "linux-yocto-fitimage:do_deploy"
MACHINE_ESSENTIAL_EXTRA_RDEPENDS:remove = "linux-yocto-fitimage"

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
