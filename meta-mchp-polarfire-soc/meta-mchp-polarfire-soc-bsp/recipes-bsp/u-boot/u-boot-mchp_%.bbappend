FILESEXTRAPATHS:prepend:mpfs := "${THISDIR}/files:"

require ${@bb.utils.contains('MACHINE_FEATURES', 'amp', 'amp-payload.inc', '', d)}

DEPENDS:append:mpfs = " python3-setuptools-native"
DEPENDS:append:mpfs = " u-boot-tools-native hss-payload-generator-native"

UBOOT_FILES:mpfs = " file://${UBOOT_ENV}.cmd \
                    file://${MACHINE}.cfg"

UBOOT_FILES:append:mpfs = "${@bb.utils.contains('MACHINE_FEATURES', 'amp', ' file://${HSS_PAYLOAD}.yaml.in', ' file://${HSS_PAYLOAD}.yaml', d)}"

SRC_URI:append:mpfs = " file://envs/"
SRC_URI:append:mpfs-icicle-kit-all = "${UBOOT_FILES}"
SRC_URI:append:mpfs-disco-kit = "${UBOOT_FILES}"
SRC_URI:append:mpfs-video-kit = "${UBOOT_FILES}"

SRC_URI:append:mpfs-icicle-kit-auth = " file://${MACHINE}.env"
SRC_URI:remove:mpfs-icicle-kit-auth = " file://${UBOOT_ENV}.cmd"

do_configure:append:mpfs-icicle-kit-auth () {
    cp -f ${WORKDIR}/${MACHINE}.env ${S}/board/microchip/mpfs_icicle
}

do_deploy:append:mpfs () {
    cp -f ${B}/${UBOOT_BINARY} ${WORKDIR}
    cd ${WORKDIR}
    hss-payload-generator -c ${WORKDIR}/${HSS_PAYLOAD}.yaml -v ${DEPLOYDIR}/payload.bin
}

do_deploy:append:mpfs-icicle-kit-auth () {

    if [ ! -f "${HSS_PAYLOAD_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem" ];then
        bbfatal "Authentication Boot file check, missing: ${HSS_PAYLOAD_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem, Refer to the Polarfire SoC Documentation"
    fi

    if [ ! -f "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt" ];then
        bbfatal "Authentication Boot file check, missing: ${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt, Refer to the Polarfire SoC Documentation"
    fi

    if [ ! -f "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" ];then
        bbfatal "Authentication Boot file check,  missing: ${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key, Refer to the Polarfire SoC Documentation"
    fi

    bbplain "Using Signing Keys Located in ${HSS_PAYLOAD_KEYDIR}"

    cd ${WORKDIR}
    hss-payload-generator -c ${WORKDIR}/${HSS_PAYLOAD}.yaml -v ${DEPLOYDIR}/payload.bin -p ${HSS_PAYLOAD_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem
}
