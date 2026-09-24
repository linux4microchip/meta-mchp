# ROM code authentication of at91bootstrap. Only the MPU ROM code has this
# stage, so this is required from common-conf.inc rather than set in the shared
# mchp-auth.inc, the same way mpfs-auth.inc and pic64gx-auth.inc carry the HSS
# payload keys for their own families.

# Second tier of the chain the ROM code walks. Named here because
# dev-signing-keys-native issues the certificate and at91bootstrap signs with
# it, so the two have to agree on the name, and config is the only scope both
# see.
MCHP_ROMCODE_SIGN_KEYNAME ?= "${UBOOT_SIGN_KEYNAME}_signing"
