SUMMARY = "Package group for Microchip’s Ensemble Graphics Toolkit (EGT) apps"
DESCRIPTION = "${SUMMARY}"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit packagegroup

PROVIDES = "${PACKAGES}"
PACKAGES = "packagegroup-mchp-egt-apps"

RDEPENDS:packagegroup-mchp-egt-apps:append:mpuall = " \
    egt-benchmark \
    egt-launcher \
    egt-media \
    egt-samples \
    egt-samples-contribution \
    egt-thermostat \
    mchp-egt-demo-init \
"
