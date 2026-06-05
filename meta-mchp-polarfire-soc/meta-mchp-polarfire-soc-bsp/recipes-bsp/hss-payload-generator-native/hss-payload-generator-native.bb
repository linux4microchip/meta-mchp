SUMMARY = "Microchip Polarfire SoC Hart Software Services (HSS) Payload Generator"
DESCRIPTION = "HSS requires U-Boot to be packaged into bootable format using HSS payload generator tool"
HOMEPAGE = "https://github.com/polarfire-soc/hart-software-services"

LICENSE = "MIT | GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE.md;md5=2cd3c5e5cf4de899b2ed773b471011f2"

inherit native

DEPENDS:append = "elfutils-native libyaml-native"

PV = "1.0+git${SRCPV}"
SRCREV = "4bea7e24f3e5ef1de360a80b0a27abb1eb6134e0"
SRC_URI = "git://github.com/polarfire-soc/hart-software-services.git;protocol=https;nobranch=1"

S = "${WORKDIR}/git"

do_compile () {
    oe_runmake -C ${S}/tools/hss-payload-generator -e CFLAGS="${CFLAGS}"
}

do_install () {
    install -d ${D}${bindir}
    install -m 755 ${S}/tools/hss-payload-generator/hss-payload-generator ${D}${bindir}
}

FILES:${PN} = "${bindir}/hss-payload-generator"
