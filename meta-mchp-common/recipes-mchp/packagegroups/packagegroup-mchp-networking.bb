SUMMARY = "Networking package group including basic network utilities."
DESCRIPTION = "${SUMMARY}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PROVIDES = "${PACKAGES}"
PACKAGES = " \
    packagegroup-mchp-networking \
"

WIFI_FIRMWARE_PACKAGES = "\
    linux-firmware-ralink \
    linux-firmware-rtl8188 \
    linux-firmware-rtl8192ce \
    linux-firmware-rtl8192cu \
    linux-firmware-rtl8192su \
    linux-firmware-rtl8723 \
    linux-firmware-rtl8821 \
    linux-firmware-sd8686 \
    linux-firmware-sd8688 \
    linux-firmware-sd8787 \
    linux-firmware-sd8797 \
    linux-firmware-sd8801 \
    linux-firmware-sd8887 \
    linux-firmware-sd8897 \
    linux-firmware-sd8997 \
    linux-firmware-mediatek \
    mchp-wireless-firmware \
"

RDEPENDS:packagegroup-mchp-networking = "\
    iproute2 \
    iptables \
    openssh-sftp \
    openssh-sftp-server \
    rsync \
    wget \
    ${@bb.utils.contains('MACHINE_FEATURES', 'wifi', WIFI_FIRMWARE_PACKAGES, '', d)} \
"
