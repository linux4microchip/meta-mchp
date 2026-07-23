FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"

SRC_URI:append = " \
    file://hostapd@.service \
    file://hostapd.conf \
    file://hostapd_open.conf \
    file://hostapd_wpa.conf \
"

do_configure:append () {
    cat ${UNPACKDIR}/hostapd.conf >> ${S}/hostapd/.config
}

do_install:append () {
    install -d ${D}${sysconfdir}/systemd/system
    install -d ${D}${sysconfdir}/network
    install -m 0644 ${UNPACKDIR}/hostapd@.service ${D}${sysconfdir}/systemd/system
    install -m 0644 ${UNPACKDIR}/hostapd_open.conf ${D}${sysconfdir}/network
    install -m 0644 ${UNPACKDIR}/hostapd_wpa.conf ${D}${sysconfdir}/network
}

FILES:{PN}:append = " \
    ${sysconfdir}/systemd/system/ \
    ${sysconfdir}/network/ \
"
