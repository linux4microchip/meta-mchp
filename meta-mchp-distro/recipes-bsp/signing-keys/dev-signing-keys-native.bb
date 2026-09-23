SUMMARY = "Development signing keys for authenticated boot"
DESCRIPTION = "Generates RSA FIT image signing keys for development use. \
These keys are NOT suitable for production. Replace with production keys \
by placing them in their directories before building."
LICENSE = "MIT"

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
        openssl req -batch -new -x509 \
            -key "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" \
            -out "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt"
    fi

    bbwarn "dev-signing-keys-native: These keys are NOT suitable for production use."
    bbwarn "dev-signing-keys-native: To use your own keys, please read the Security Features section of the readme"
}
do_compile[vardeps] += "UBOOT_SIGN_KEYNAME UBOOT_SIGN_KEYDIR"
