### dm-verity ###
UBI_IMGTYPE:mchp-dm-verity = "${DM_VERITY_IMAGE_TYPE}.verity"
OVERLAYFS_ETC_DEVICE:mchp-dm-verity = "ubi0:data"
OVERLAYFS_ETC_FSTYPE:mchp-dm-verity = "ubifs"

#inherit bbclass
IMAGE_CLASSES:append:mchp-dm-verity = " mchp-ubi-verity"

# The initramfs needs 79-ubiblock to turn root=ubi0:rootfs into a block device
# before 80-dmverity runs. Scoped with pn- rather than a bbappend: meta-security
# is not in LAYERDEPENDS, so an unconditional bbappend on its recipe would be a
# parse error in any build without that layer.
PACKAGE_INSTALL:append:pn-dm-verity-image-initramfs = " initramfs-module-ubiblock"
