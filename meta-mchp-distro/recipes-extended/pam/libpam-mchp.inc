FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"

SRC_URI:append = " file://updatecommon-session"

do_install:append() {
   install -m 0644 ${UNPACKDIR}/updatecommon-session ${D}${sysconfdir}/pam.d/common-session
}
