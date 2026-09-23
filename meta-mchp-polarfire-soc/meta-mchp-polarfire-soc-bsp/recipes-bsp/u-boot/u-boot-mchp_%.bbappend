FILESEXTRAPATHS:prepend:mpfs := "${THISDIR}/files:"

require ${@bb.utils.contains('MACHINE_FEATURES', 'amp', 'amp-payload.inc', '', d)}

DEPENDS:append:mpfs = " python3-setuptools-native"
DEPENDS:append:mpfs = " u-boot-tools-native hss-payload-generator-native"

UBOOT_FILES:mpfs = "file://${UBOOT_ENV}.cmd \
                    file://${MACHINE}.cfg"

UBOOT_FILES:append:mpfs = "${@bb.utils.contains('MACHINE_FEATURES', 'amp', ' file://${HSS_PAYLOAD}.yaml.in', ' file://${HSS_PAYLOAD}.yaml', d)}"

SRC_URI:append:mpfs = " file://envs/"
SRC_URI:append:mpfs-icicle-kit-all = " ${UBOOT_FILES}"
SRC_URI:append:mpfs-disco-kit = " ${UBOOT_FILES}"
SRC_URI:append:mpfs-video-kit = " ${UBOOT_FILES}"
SRC_URI:append:mpfs:mchp-auth = " file://mchp-auth.cfg"

do_deploy:append:mpfs () {
    cp -f ${B}/${UBOOT_BINARY} ${UNPACKDIR}
    cd ${UNPACKDIR}

    if ${@bb.utils.contains('DISTRO_FEATURES', 'mchp-auth', 'true', 'false', d)}; then
        if [ ! -f "${HSS_SIGN_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem" ]; then
            bbfatal "Authentication Boot file check, missing: ${HSS_SIGN_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem, Refer to the Polarfire SoC Documentation"
        fi

        if [ ! -f "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt" ]; then
            bbfatal "Authentication Boot file check, missing: ${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt, Refer to the Polarfire SoC Documentation"
        fi

        if [ ! -f "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" ]; then
            bbfatal "Authentication Boot file check, missing: ${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key, Refer to the Polarfire SoC Documentation"
        fi

        bbplain "Using U-Boot Signing Keys Located in ${UBOOT_SIGN_KEYDIR}"
        bbplain "Using HSS Signing Keys Located in ${HSS_SIGN_KEYDIR}"
        hss-payload-generator -c ${UNPACKDIR}/${HSS_PAYLOAD}.yaml -v ${DEPLOYDIR}/payload.bin -p ${HSS_SIGN_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem
    else
        hss-payload-generator -c ${UNPACKDIR}/${HSS_PAYLOAD}.yaml -v ${DEPLOYDIR}/payload.bin
    fi
}
