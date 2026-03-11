HOMEPAGE = "https://github.com/ikwzm/udmabuf"
SUMMARY = "User space mappable dma buffer device driver for Linux"
DESCRIPTION = "User space mappable dma buffer device driver for Linux"
LICENSE = "BSD-2-Clause"
LIC_FILES_CHKSUM = "file://LICENSE;md5=bebf0492502927bef0741aa04d1f35f5"

inherit module

S = "${WORKDIR}/git"

SRC_URI = "git://github.com/ikwzm/udmabuf;branch=master;protocol=https"
SRCREV = "cff954eb557db73a5196f12d16c687c5cb96eb32"
PV = "5.4.2"

RPROVIDES:${PN} += "kernel-module-udmabuf"
