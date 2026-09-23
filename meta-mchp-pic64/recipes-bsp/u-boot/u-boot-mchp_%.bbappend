FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

DEPENDS:append:pic64gx = " python3-setuptools-native"
DEPENDS:append:pic64gx = " u-boot-tools-native pic64gx-hss-payload-generator-native"

UBOOT_FILES = "file://${UBOOT_ENV}.cmd \
               file://${MACHINE}.cfg"

UBOOT_FILES:append:pic64gx-curiosity-kit = " file://${HSS_PAYLOAD}.yaml"
UBOOT_FILES:append:pic64gx-curiosity-kit-amp = " file://${HSS_PAYLOAD}.yaml.in"

SRC_URI:append:pic64gx = " file://envs/"
SRC_URI:append:pic64gx = " ${UBOOT_FILES}"
SRC_URI:append:pic64gx:mchp-auth = " file://mchp-auth.cfg"

do_deploy:append (){
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

do_deploy:prepend:pic64gx-curiosity-kit-amp () {
    sed \
        -e "s/@@AMP_DEMO@@/null/g" \
        -e "s/@@AMP_PAYLOAD@@/null/g" \
        -e "s/@@AMP_SKIP-AUTOBOOT@@/true/g" \
        ${UNPACKDIR}/${HSS_PAYLOAD}.yaml.in > ${UNPACKDIR}/${HSS_PAYLOAD}.yaml
}

COMPATIBLE_MACHINE:append:pic64gx-curiosity-kit = "|pic64gx-curiosity-kit"
