FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    file://0001-configs-Set-default-PTP-minor-version-to-0.patch \
    "
