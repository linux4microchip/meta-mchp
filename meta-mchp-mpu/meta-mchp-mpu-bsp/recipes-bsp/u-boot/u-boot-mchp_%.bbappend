FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " file://envs/"
SRC_URI:append:mpuall:mchp-dm-verity = " file://dm-verity-bootm-len.cfg"

inherit mchp-compat-machines
