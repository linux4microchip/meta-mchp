SUMMARY = "PIC64GX zephyr example with OpenAMP"
DESCRIPTION = "PIC64GX zephyr example with OpenAMP"

require pic64gx-zephyr-amp.inc

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV_pic64-zephyr-examples = "e695942408e44e4ccccc5b8823c7c17e14267681"
SRC_URI_APP = "git://github.com/pic64gx/pic64gx-zephyr-examples.git;protocol=https;subpath=apps/amp_example_openamp"
SRC_URI:append = " ${SRC_URI_APP};name=pic64-zephyr-examples;nobranch=1;destsuffix=git/pic64gx-soc/apps/amp_example_openamp "

ZEPHYR_SRC_DIR = "${WORKDIR}/git/pic64gx-soc/apps/amp_example_openamp"

EXTRA_OECMAKE += " \
    -DCONFIG_PIC64GX_RELOCATE_RESOURCE_TABLE=y \
    -DCMAKE_CXX_FLAGS=-fdebug-prefix-map=${TMPDIR}=${TARGET_DBGSRC_DIR} \
    "

do_install() {
    install -Dm 0644 ${B}/zephyr/${ZEPHYR_MAKE_OUTPUT} ${D}/usr/lib/firmware/${PN}.elf
}

do_deploy() {
    cp ${B}/zephyr/${ZEPHYR_MAKE_OUTPUT} ${DEPLOYDIR}/${PN}.elf
}

FILES:${PN} += "/usr/lib/firmware/${PN}.elf"
SYSROOT_DIRS += "/usr/lib/firmware"
INSANE_SKIP += "ldflags buildpaths"

COMPATIBLE_MACHINE:append:pic64gx-curiosity-kit = "|pic64gx-curiosity-kit"
