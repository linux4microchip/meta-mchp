SUMMARY = "Vivante nano2D kernel module"
DESCRIPTION = "${SUMMARY}"
HOMEPAGE = "https://github.com/linux4sam/nano2d"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://git/LICENSE.txt;md5=d273f77f5527ec3b62511e2365d1d436"

inherit module

SRC_URI = "file://Makefile \
           git://github.com/linux4sam/nano2d.git;protocol=https;branch=master \
          "

SRCREV = "1aee6694e574adccd625e87ebb37314da7f170b9"

S = "${WORKDIR}"

MODULES_MODULE_SYMVERS_LOCATION = "git/drv/nano2Dkernel"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES:${PN} += "kernel-module-nano2d"
KERNEL_MODULE_AUTOLOAD += "nano2d"
