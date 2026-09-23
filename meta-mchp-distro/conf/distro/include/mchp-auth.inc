# Authenticated boot configuration for Microchip platforms
# This file is included when 'mchp-auth' is in DISTRO_FEATURES

# FIT image signing (RSA)
UBOOT_SIGN_ENABLE ?= "1"
UBOOT_SIGN_KEYNAME ?= "${@bb.utils.contains('MCHP_DEV_SIGNING_KEYS', '1', 'dev_', '', d)}${MACHINE}_fitimage_key"
UBOOT_SIGN_KEYDIR ?= "${TOPDIR}/../keys"
UBOOT_MKIMAGE_DTCOPTS ?= "-I dts -O dtb -p 2000"

FIT_SIGN_ALG ?= "rsa4096"
FIT_HASH_ALG ?= "sha256"
