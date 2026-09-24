FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " file://envs/"
SRC_URI:append:mpuall:mchp-dm-verity = " file://dm-verity-bootm-len.cfg"
SRC_URI:append:mchp-auth = " file://mchp-auth.cfg"

inherit mchp-compat-machines
