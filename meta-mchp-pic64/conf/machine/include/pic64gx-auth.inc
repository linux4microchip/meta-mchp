# HSS payload signing (ECDSA secp384r1)
HSS_PAYLOAD_PRIVATE_KEYNAME ?= "${@bb.utils.contains('MCHP_DEV_SIGNING_KEYS', '1', 'dev_', '', d)}x509-ec-secp384r1-private"
HSS_PAYLOAD_PUBLIC_KEYNAME ?= "${@bb.utils.contains('MCHP_DEV_SIGNING_KEYS', '1', 'dev_', '', d)}x509-ec-secp384r1-public"
HSS_SIGN_KEYDIR ?= "${TOPDIR}/../keys"
