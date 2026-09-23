FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'mchp-dm-verity', 'file://dm-verity.cfg','', d)} \
"
