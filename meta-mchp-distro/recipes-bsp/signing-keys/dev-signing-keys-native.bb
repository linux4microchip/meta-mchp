SUMMARY = "Development signing keys for authenticated boot"
DESCRIPTION = "Generates RSA FIT image signing keys for development use. \
These keys are NOT suitable for production. Replace with production keys \
by placing them in their directories before building."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "openssl-native"
inherit native

do_fetch[noexec] = "1"
do_unpack[noexec] = "1"
do_patch[noexec] = "1"
do_configure[noexec] = "1"
do_install[noexec] = "1"

do_compile[nostamp] = "1"

do_compile() {
    install -d "${UBOOT_SIGN_KEYDIR}"

    if [ ! -f "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" ]; then
        bbwarn "dev-signing-keys-native: Generating DEV RSA FIT image signing keys in ${UBOOT_SIGN_KEYDIR}."
        openssl genrsa -F4 -out "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" 4096
        # -days, because 'openssl req -x509' otherwise issues for 30 days and
        # the root expires a month after the build. It is the root of trust for
        # the FIT and, on MPU, of the chain the ROM code walks, so anything
        # certified under it stops verifying when it lapses. -sha256 and an
        # explicit serial rather than the random one openssl picks.
        openssl req -batch -new -x509 -sha256 -days 2922 -set_serial 0x101 \
            -key "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" \
            -out "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt" \
            -subj "/O=Microchip Technology/CN=${UBOOT_SIGN_KEYNAME}"
    fi

    bbwarn "dev-signing-keys-native: These keys are NOT suitable for production use."
    bbwarn "dev-signing-keys-native: To use your own keys, please read the Security Features section of the readme"
}
do_compile[vardeps] += "UBOOT_SIGN_KEYNAME UBOOT_SIGN_KEYDIR"
