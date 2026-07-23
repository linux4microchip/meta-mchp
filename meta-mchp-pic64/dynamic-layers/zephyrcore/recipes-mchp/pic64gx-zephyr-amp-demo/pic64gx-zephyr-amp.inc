# Zephyr AMP Common requirements

inherit zephyr-sample

# Substitute Zephyr kernel with our fork, for the moment we do that, it might
# be wise to just recreate a custom zephyr-kernel-src-x.bb at some point with
# our forks
ZEPHYR_BRANCH = "v4.4.0-mchp"
SRCREV_default = "799c3f61f89e5602212b5cfc7de5f5e630de90f1"
SRC_URI_ZEPHYR = "git://github.com/pic64gx/pic64gx-zephyr.git;protocol=file"
SRC_URI:append = " ${SRC_URI_ZEPHYR};nobranch=1;name=default;destsuffix=git/zephyr "

SRCREV_open-amp = "01032a8a7bdfdd541686f5dfa3671e602b9fcbff"
SRC_URI_ZEPHYR_OPENAMP = "git://github.com/zephyrproject-rtos/open-amp.git;protocol=https"
SRC_URI:append = " ${SRC_URI_ZEPHYR_OPENAMP};name=open-amp;nobranch=1;destsuffix=git/modules/lib/open-amp "

SRCREV_libmetal = "c41f476ba425663cadf7e456b6432e4b21591278"
SRC_URI_ZEPHYR_LIBMETAL = "git://github.com/zephyrproject-rtos/libmetal.git;protocol=https"
SRC_URI:append = " ${SRC_URI_ZEPHYR_LIBMETAL};name=libmetal;nobranch=1;destsuffix=git/modules/hal/libmetal "

ZEPHYR_MODULES:append = " ${S}/modules/lib/open-amp\;"
ZEPHYR_MODULES:append = " ${S}/modules/hal/libmetal\;"

BOARD_DIR = "${S}/zephyr/boards/${ARCH}/${ZEPHYR_BOARD}"
