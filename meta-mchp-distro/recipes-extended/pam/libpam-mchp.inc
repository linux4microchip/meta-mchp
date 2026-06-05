FILESEXTRAPATHS:prepend := "${THISDIR}/files/:"

SRC_URI:append = " file://updatecommon-session"

do_install:append() {
   install -m 0644 ${WORKDIR}/updatecommon-session ${D}${sysconfdir}/pam.d/common-session
}
