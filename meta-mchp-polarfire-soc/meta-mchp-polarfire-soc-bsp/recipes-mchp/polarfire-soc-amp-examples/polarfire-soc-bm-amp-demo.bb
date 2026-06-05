SUMMARY = "Polarfire SoC Bare-metal AMP demo applications"
DESCRIPTION = "Demo Bare-metal application to run in AMP build \
along with a Linux context"
HOMEPAGE = "https://github.com/polarfire-soc/polarfire-soc-amp-examples"

require polarfire-soc-amp-demo.inc

do_install() {
    install -Dm 0644 ${S}/mpfs-rpmsg-bm/Remote-Default/mpfs-rpmsg-remote.elf ${D}/usr/lib/firmware/${PN}.elf
}

do_compile() {
   oe_runmake -C ${S}/mpfs-rpmsg-bm
}

do_deploy() {
    install -m 755 ${S}/mpfs-rpmsg-bm/Remote-Default/mpfs-rpmsg-remote.elf ${DEPLOYDIR}/${PN}.elf
}
