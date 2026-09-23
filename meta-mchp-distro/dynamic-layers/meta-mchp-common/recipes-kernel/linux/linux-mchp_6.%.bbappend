FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'mchp-dm-verity', 'file://dm-verity.cfg','', d)} \
"
DEPENDS:append:mchp-auth = " ${@bb.utils.contains('MCHP_DEV_SIGNING_KEYS', '1', 'dev-signing-keys-native', '', d)}"
