RDEPENDS:${PN}-multimedia += "\
    fswebcam \
    gstd \
    gstreamer1.0-plugins-base-videotestsrc \
    gstreamer1.0-plugins-good \
    media-ctl \
    v4l-utils \
"

PACKAGES += "\
    ${PN}-multimedia \
"

INSANE_SKIP:${PN}-multimedia += "file-rdeps ldflags debug-files"

EXAMPLE_FILES += "\
    multimedia \
"

FILES:${PN}-multimedia += "/opt/microchip/multimedia/"
