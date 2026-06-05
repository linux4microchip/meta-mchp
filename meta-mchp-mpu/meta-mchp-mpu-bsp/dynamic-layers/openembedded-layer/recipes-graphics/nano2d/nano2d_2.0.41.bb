SUMMARY = "Vivante nano2D user-space library"
DESCRIPTION = "${SUMMARY}"
HOMEPAGE = "https://github.com/linux4sam/nano2d"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=d273f77f5527ec3b62511e2365d1d436"

RDEPENDS:${PN} = "kernel-module-nano2d"

inherit pkgconfig cmake

SRC_URI = "git://github.com/linux4sam/nano2d.git;protocol=https;branch=master"

SRCREV = "1aee6694e574adccd625e87ebb37314da7f170b9"

S = "${WORKDIR}/git"
