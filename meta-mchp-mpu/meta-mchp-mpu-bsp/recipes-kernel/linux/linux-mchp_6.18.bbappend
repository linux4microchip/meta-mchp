FILESEXTRAPATHS:prepend := "${THISDIR}/${BP}:"

SRC_URI:append:sama7g5 = " file://libcamera.cfg"
SRC_URI:append:sam9x75 = " file://libcamera.cfg"

SRC_URI:append:sama7d65 = " ${@bb.utils.contains('MACHINE_FEATURES',\
                            'wifi', 'file://wifi/wireless-fragment.cfg', '', d)}"
SRC_URI:append:sam9x75  = " ${@bb.utils.contains('MACHINE_FEATURES',\
                            'wifi', 'file://wifi/wireless-fragment.cfg', '', d)}"
