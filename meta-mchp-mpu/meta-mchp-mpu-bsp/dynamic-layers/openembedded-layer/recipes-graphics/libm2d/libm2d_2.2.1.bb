DESCRIPTION = "Microchip libm2d library to abstract 2D GPUs and provide a common API"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://COPYING;endline=202;md5=3b83ef96387f14655fc854ddc3c6bd57"

DEPENDS = "cairo libdrm libplanes"
DEPENDS:append:sama7d65 = " nano2d"

SRC_URI = "git://github.com/linux4sam/libm2d.git;protocol=https;branch=master"

SRCREV = "807cfebf738a4abea841e9b30b61aa3ea7a18705"

S = "${WORKDIR}/git"

EXTRA_OECMAKE += " \
    -DENABLE_TESTS=1 \
"

EXTRA_OECMAKE:append:sam9x60 = " -DGPU=microchip,sam9x60-gfx2d"
EXTRA_OECMAKE:append:sam9x75 = " -DGPU=microchip,sam9x7-gfx2d"
EXTRA_OECMAKE:append:sama7d65 = " -DGPU=vivante,gc-nano2d"

inherit pkgconfig cmake

FILES:${PN} += " \
    ${datadir}/m2d/* \
"
