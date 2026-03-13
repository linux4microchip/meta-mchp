DEPENDS:append:pic64gx-curiosity-kit-amp = " pic64gx-zephyr-amp-demo"

do_deploy:append () {
    if ${@bb.utils.contains('MACHINE_FEATURES', 'amp', 'true', 'false', d)}; then
        if ${@bb.utils.contains('DISTRO_FEATURES', 'hss-early-boot-zephyr', 'true', 'false', d)}; then
            cp -f ${DEPLOY_DIR_IMAGE}/pic64gx-zephyr-amp-demo.elf ${WORKDIR}
            sed \
                -e "s/@@AMP_DEMO@@/zephyr/g" \
                -e "s/@@AMP_PAYLOAD@@/pic64gx-zephyr-amp-demo.elf/g" \
                -e "s/@@AMP_SKIP-AUTOBOOT@@/false/g" \
                ${WORKDIR}/${HSS_PAYLOAD}.yaml.in > ${WORKDIR}/${HSS_PAYLOAD}.yaml
            cd ${WORKDIR}
            hss-payload-generator -c ${WORKDIR}/${HSS_PAYLOAD}.yaml -v ${DEPLOYDIR}/payload.bin
        fi
    fi
}
