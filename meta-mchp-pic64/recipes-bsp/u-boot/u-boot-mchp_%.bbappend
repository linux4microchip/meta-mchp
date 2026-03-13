FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

DEPENDS:append:pic64gx = " python3-setuptools-native"
DEPENDS:append:pic64gx = " u-boot-tools-native pic64gx-hss-payload-generator-native"

UBOOT_FILES = " file://${UBOOT_ENV}.cmd \
                file://${MACHINE}.cfg"

UBOOT_FILES:append:pic64gx-curiosity-kit = " file://${HSS_PAYLOAD}.yaml"
UBOOT_FILES:append:pic64gx-curiosity-kit-amp = " file://${HSS_PAYLOAD}.yaml.in"

SRC_URI:append:pic64gx = " file://envs/"
SRC_URI:append:pic64gx = "${UBOOT_FILES}"

do_deploy:append (){
    cp -f ${B}/${UBOOT_BINARY} ${WORKDIR}
    cd ${WORKDIR}
    hss-payload-generator -c ${WORKDIR}/${HSS_PAYLOAD}.yaml -v ${DEPLOYDIR}/payload.bin
}

do_deploy:prepend:pic64gx-curiosity-kit-amp () {
    sed \
        -e "s/@@AMP_DEMO@@/null/g" \
        -e "s/@@AMP_PAYLOAD@@/null/g" \
        -e "s/@@AMP_SKIP-AUTOBOOT@@/true/g" \
        ${WORKDIR}/${HSS_PAYLOAD}.yaml.in > ${WORKDIR}/${HSS_PAYLOAD}.yaml
}

COMPATIBLE_MACHINE:append:pic64gx-curiosity-kit = "|pic64gx-curiosity-kit"
