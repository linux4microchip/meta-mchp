SUMMARY = "Package group for security software."
DESCRIPTION = "${SUMMARY}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PROVIDES = "${PACKAGES}"
PACKAGES = "packagegroup-mchp-security"

RDEPENDS:packagegroup-mchp-security = "\
    p11-kit \
"
