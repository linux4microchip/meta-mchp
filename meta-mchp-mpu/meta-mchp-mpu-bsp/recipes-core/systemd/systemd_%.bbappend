# Drop systemd's OSC 3008 shell-prompt hook.
#
# systemd >= 258 ships /etc/profile.d/80-systemd-osc-context.sh, a bash
# PROMPT_COMMAND/PS0 pair that emits OSC 3008 "hierarchical context" sequences
# (UAPI.15) around every prompt and every command:
#
#   printf "\033]3008;start=%s;...;type=shell;cwd=%s\033\\" ...
#   printf "\033]3008;end=%s;exit=success\033\\" ...

FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://10-no-ansi-reset.conf"

do_install:append() {
	install -d ${D}${systemd_system_unitdir}/serial-getty@.service.d
	install -m 0644 ${UNPACKDIR}/10-no-ansi-reset.conf \
		${D}${systemd_system_unitdir}/serial-getty@.service.d/
}
