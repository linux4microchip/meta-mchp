SUMMARY = "Microchip libcamera framework — migration to upstream v0.7.0 base"
DESCRIPTION = "${SUMMARY}"
HOMEPAGE = "https://github.com/linux4microchip/libcamera-mchp"
SECTION = "libs"
LICENSE = "GPL-2.0-or-later & LGPL-2.1-or-later"
LIC_FILES_CHKSUM = "\
    file://LICENSES/GPL-2.0-or-later.txt;md5=fed54355545ffd980b814dab4a3b312c \
    file://LICENSES/LGPL-2.1-or-later.txt;md5=2a4f4fd2128ea2f65047ee63fbca9f68 \
"

# Tracks mchp-next-v0.7.0 on the linux4microchip GitHub fork, based on
# upstream libcamera v0.7.0. The legacy libcamera-mchp_0.3.1.bb is
# retained for BSP releases prior to linux4microchip-2026.04.
SRC_URI = "git://github.com/linux4microchip/libcamera-mchp.git;protocol=https;branch=mchp-next-v0.7.0"

SRCREV = "8d6f2a0cc4443a33abd8d407799fccd3b139efb3"

PE = "1"
PV = "0.7.0+mchp-${SRCPV}"
S = "${WORKDIR}/git"

DEPENDS = "\
    chrpath-native \
    gnutls \
    jpeg \
    libevent \
    libpng \
    libyaml \
    python3-jinja2-native \
    python3-ply-native \
    python3-pyyaml-native \
    udev \
"

DEPENDS \
+= "${@bb.utils.contains('DISTRO_FEATURES', 'qt', 'qtbase qtbase-native', '', d)}"

PACKAGES =+ "${PN}-apps ${PN}-gst ${PN}-pycamera ${PN}-ipa ${PN}-pipelines"

PACKAGECONFIG ??= "mchpcam gst ipas"
PACKAGECONFIG[gst]      = "-Dgstreamer=enabled,-Dgstreamer=disabled,gstreamer1.0 gstreamer1.0-plugins-base"
PACKAGECONFIG[pycamera] = "-Dpycamera=enabled,-Dpycamera=disabled,python3 python3-pybind11"
PACKAGECONFIG[mchpcam]  = "-Dmchpcam=enabled,-Dmchpcam=disabled"
PACKAGECONFIG[ipas]     = "-Dipas=microchip-isc,-Dipas=none"

LIBCAMERA_PIPELINES ??= "microchip-isc"

EXTRA_OEMESON = "\
    -Dpipelines=${LIBCAMERA_PIPELINES} \
    -Dv4l2=true \
    -Dcam=enabled \
    -Dmchpcam=${@bb.utils.contains('PACKAGECONFIG', 'mchpcam', 'enabled', 'disabled', d)} \
    -Dlc-compliance=disabled \
    -Dtest=false \
    -Ddocumentation=disabled \
    -Dipas=microchip-isc \
"

RDEPENDS:${PN} = "${PN}-ipa \
    ${@bb.utils.contains('DISTRO_FEATURES', 'wayland qt', 'qtwayland', '', d)}"

inherit meson pkgconfig python3native

do_configure:prepend() {
    sed -i -e 's|py_compile=True,||' ${S}/utils/codegen/ipc/mojo/public/tools/mojom/mojom/generate/template_expander.py
}

do_install:append() {
    chrpath -d ${D}${libdir}/libcamera.so.0.7.0
    chrpath -d ${D}${libdir}/libcamera-base.so.0.7.0
    chrpath -d ${D}${libexecdir}/libcamera/v4l2-compat.so

    if ${@bb.utils.contains('PACKAGECONFIG', 'mchpcam', 'true', 'false', d)}; then
        install -d ${D}${bindir}
        if [ -f ${B}/src/apps/mchpcam/mchpcam-still ]; then
            install -m 0755 ${B}/src/apps/mchpcam/mchpcam-still ${D}${bindir}
        fi
    fi
}

do_package:append() {
    bb.build.exec_func("do_package_recalculate_ipa_signatures", d)
}

# IPA path changed to {libdir}/libcamera/ipa/ subdir in v0.7.0
do_package_recalculate_ipa_signatures() {
    local modules
    for module in $(find ${PKGD}${libdir}/libcamera/ipa -name "*.so.sign"); do
        module="${module%.sign}"
        if [ -f "${module}" ]; then
            modules="${modules} ${module}"
        fi
    done
    ${S}/src/ipa/ipa-sign-install.sh ${B}/src/ipa-priv-key.pem "${modules}"
}

FILES:${PN} += "\
    ${libexecdir}/libcamera/v4l2-compat.so \
    ${libexecdir}/libcamera/microchip_isc_ipa_proxy \
    ${libdir}/libcamera.so.* \
    ${libdir}/libcamera-base.so.* \
    ${datadir}/libcamera/ipa/microchip-isc \
"
FILES:${PN}-apps    += "${bindir}/cam ${bindir}/libcamerify ${bindir}/mchpcam-*"
FILES:${PN}-gst     += "${libdir}/gstreamer-1.0"
FILES:${PN}-ipa     += "${libdir}/libcamera/ipa/ipa_*.so ${libdir}/libcamera/ipa/ipa_*.so.sign"
FILES:${PN}-pipelines += "${datadir}/libcamera/pipeline"
FILES:${PN}-pycamera += "${PYTHON_SITEPACKAGES_DIR}/libcamera"

# libcamera-v4l2 explicitly sets _FILE_OFFSET_BITS=32 to get access to
# both 32 and 64 bit file APIs.
GLIBC_64BIT_TIME_FLAGS = ""
INSANE_SKIP += "32bit-time"
