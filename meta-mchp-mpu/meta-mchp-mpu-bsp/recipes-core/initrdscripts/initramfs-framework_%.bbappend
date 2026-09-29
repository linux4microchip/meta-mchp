# Adds /init.d/79-ubiblock, which rewrites root=ubi<N>:<vol> into the matching
# /dev/ubiblock node so that 80-dmverity is handed a real block device.
#
# Gated on the mchp-dm-verity DISTRO_FEATURE *only*

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append:mchp-dm-verity = " file://ubiblock"

do_install:append:mchp-dm-verity() {
    install -m 0755 ${S}/ubiblock ${D}/init.d/79-ubiblock
}

PACKAGES:append:mchp-dm-verity = " initramfs-module-ubiblock"

SUMMARY:initramfs-module-ubiblock = "initramfs support for a UBI block root device"
RDEPENDS:initramfs-module-ubiblock = "${PN}-base"
FILES:initramfs-module-ubiblock = "/init.d/79-ubiblock"
