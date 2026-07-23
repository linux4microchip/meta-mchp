FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " file://harden_sshd_config.cfg"

do_install:append() {
    cat ${UNPACKDIR}/harden_sshd_config.cfg >> ${D}${sysconfdir}/ssh/sshd_config
}
