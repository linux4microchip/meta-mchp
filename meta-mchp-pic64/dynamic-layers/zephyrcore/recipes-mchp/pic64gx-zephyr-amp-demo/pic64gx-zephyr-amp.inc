# Zephyr AMP Common requirements

inherit zephyr-sample

# Substitute Zephyr kernel with our fork, for the moment we do that, it might
# be wise to just recreate a custom zephyr-kernel-src-x.bb at some point with
# our forks
ZEPHYR_BRANCH = "v4.4.0-mchp"
SRCREV_default = "4f46662ffb014fe30b74ac7c25a2d2ede7894b33"
SRC_URI_ZEPHYR = "git://github.com/pic64gx/pic64gx-zephyr.git;protocol=https"
SRC_URI:append = " ${SRC_URI_ZEPHYR};nobranch=1;name=default;destsuffix=${P}/zephyr "

SRCREV_open-amp = "5efe7974f9546582e99f5a842a816ea4b65f5227"
SRC_URI_ZEPHYR_OPENAMP = "git://github.com/zephyrproject-rtos/open-amp.git;protocol=https"
SRC_URI:append = " ${SRC_URI_ZEPHYR_OPENAMP};name=open-amp;nobranch=1;destsuffix=${P}/modules/lib/open-amp "

SRCREV_libmetal = "66e084293b2a7ced5a73fbd247deddba8915883a"
SRC_URI_ZEPHYR_LIBMETAL = "git://github.com/zephyrproject-rtos/libmetal.git;protocol=https"
SRC_URI:append = " ${SRC_URI_ZEPHYR_LIBMETAL};name=libmetal;nobranch=1;destsuffix=${P}/modules/hal/libmetal "

ZEPHYR_MODULES:append = " ${S}/modules/lib/open-amp\;"
ZEPHYR_MODULES:append = " ${S}/modules/hal/libmetal\;"

BOARD_DIR = "${S}/zephyr/boards/${ARCH}/${ZEPHYR_BOARD}"
