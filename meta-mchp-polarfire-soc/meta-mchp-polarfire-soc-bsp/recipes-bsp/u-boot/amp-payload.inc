inherit features_check

REQUIRED_MACHINE_FEATURES = "amp"

CONFLICT_DISTRO_FEATURES:hss-early-boot-freertos = "hss-early-boot-bm"
CONFLICT_DISTRO_FEATURES:hss-early-boot-bm = "hss-early-boot-freertos"

DEPENDS:append = "${@bb.utils.contains('DISTRO_FEATURES', 'hss-early-boot-freertos', ' polarfire-soc-freertos-amp-demo', '', d)}"
DEPENDS:append = "${@bb.utils.contains('DISTRO_FEATURES', 'hss-early-boot-bm',        ' polarfire-soc-bm-amp-demo',        '', d)}"

do_deploy:prepend () {
    if ${@bb.utils.contains('DISTRO_FEATURES', 'hss-early-boot-freertos', 'true', 'false', d)}; then
        cp -f ${DEPLOY_DIR_IMAGE}/polarfire-soc-freertos-amp-demo.elf ${WORKDIR}
        sed \
            -e "s/@@AMP_DEMO@@/freertos/g" \
            -e "s/@@AMP_PAYLOAD@@/polarfire-soc-freertos-amp-demo.elf/g" \
            -e "s/@@AMP_SKIP-AUTOBOOT@@/false/g" \
            ${WORKDIR}/${HSS_PAYLOAD}.yaml.in > ${WORKDIR}/${HSS_PAYLOAD}.yaml

    elif ${@bb.utils.contains('DISTRO_FEATURES', 'hss-early-boot-bm', 'true', 'false', d)}; then
        cp -f ${DEPLOY_DIR_IMAGE}/polarfire-soc-bm-amp-demo.elf ${WORKDIR}
        sed \
            -e "s/@@AMP_DEMO@@/bm/g" \
            -e "s/@@AMP_PAYLOAD@@/polarfire-soc-bm-amp-demo.elf/g" \
            -e "s/@@AMP_SKIP-AUTOBOOT@@/false/g" \
            ${WORKDIR}/${HSS_PAYLOAD}.yaml.in > ${WORKDIR}/${HSS_PAYLOAD}.yaml

    else
        sed \
            -e "s/@@AMP_DEMO@@/null/g" \
            -e "s/@@AMP_PAYLOAD@@/null/g" \
            -e "s/@@AMP_SKIP-AUTOBOOT@@/true/g" \
            ${WORKDIR}/${HSS_PAYLOAD}.yaml.in > ${WORKDIR}/${HSS_PAYLOAD}.yaml
    fi
}
