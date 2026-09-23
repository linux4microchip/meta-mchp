DEPENDS:append:mchp-auth = " ${@bb.utils.contains('MCHP_DEV_SIGNING_KEYS', '1', 'dev-signing-keys-native', '', d)}"

# On authenticated builds, force a clean u-boot rebuild when the signing key
# name changes. uboot-sign.bbclass injects the pubkey into u-boot.dtb in place,
# and ${B} persists between builds, so a renamed key would otherwise leave the
# stale key's signature node behind and fail FIT verification. Wiping ${B} in
# do_configure (which then regenerates .config) guarantees a fresh unsigned dtb.
do_configure[cleandirs] = "${@bb.utils.contains('DISTRO_FEATURES', 'mchp-auth', d.getVar('B'), '', d)}"
do_configure[vardeps] += "${@bb.utils.contains('DISTRO_FEATURES', 'mchp-auth', 'UBOOT_SIGN_KEYNAME', '', d)}"
