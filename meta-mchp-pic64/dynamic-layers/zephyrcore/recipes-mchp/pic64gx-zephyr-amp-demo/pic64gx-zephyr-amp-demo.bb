SUMMARY = "PIC64GX zephyr example with OpenAMP"
DESCRIPTION = "PIC64GX zephyr example with OpenAMP"
HOMEPAGE = "https://github.com/pic64gx/pic64gx-zephyr-examples"

require pic64gx-zephyr-amp.inc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV_pic64-zephyr-examples = "6c08ed531b93349fe746ac3697652cd979ce32ba"
SRC_URI_APP = "git://github.com/pic64gx/pic64gx-zephyr-examples.git;protocol=https;subpath=apps/amp_example_openamp"
SRC_URI:append = " ${SRC_URI_APP};name=pic64-zephyr-examples;nobranch=1;destsuffix=git/pic64gx-soc/apps/amp_example_openamp "

ZEPHYR_SRC_DIR = "${UNPACKDIR}/git/pic64gx-soc/apps/amp_example_openamp"

EXTRA_OECMAKE += "\
    -DCONFIG_PIC64GX_RELOCATE_RESOURCE_TABLE=y \
    -DCMAKE_CXX_FLAGS=-fdebug-prefix-map=${TMPDIR}=${TARGET_DBGSRC_DIR} \
"

ZEPHYR_MAKE_OUTPUT = "zephyr.elf"

do_install() {
    install -d ${D}/usr/lib/firmware
    install -m 0644 ${B}/zephyr/${ZEPHYR_MAKE_OUTPUT} ${D}/usr/lib/firmware/${PN}.elf
}

do_deploy() {
    cp ${B}/zephyr/${ZEPHYR_MAKE_OUTPUT} ${DEPLOYDIR}/${PN}.elf
}

FILES:${PN} += "/usr/lib/firmware/${PN}.elf"
SYSROOT_DIRS += "/usr/lib/firmware"
INSANE_SKIP += "ldflags buildpaths"

COMPATIBLE_MACHINE:append:pic64gx-curiosity-kit = "|pic64gx-curiosity-kit"
