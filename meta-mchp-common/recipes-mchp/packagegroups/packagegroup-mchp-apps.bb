SUMMARY = "Package group for Microchip apps and software."
DESCRIPTION = "${SUMMARY}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PROVIDES = "${PACKAGES}"
PACKAGES = "packagegroup-mchp-apps"

RDEPENDS:packagegroup-mchp-apps = "\
"
