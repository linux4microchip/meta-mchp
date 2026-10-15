SUMMARY = "Lohit Indic fonts"
DESCRIPTION = "${SUMMARY}"
HOMEPAGE = "https://pagure.io/lohit"
LICENSE = "OFL-1.1"
LIC_FILES_CHKSUM = "file://OFL.txt;md5=7dfa0a236dc535ad2d2548e6170c4402"

# The upstream releases.pagure.org tarballs are no longer available, so build
# from the upstream git repository (also used by meta-oe ttf-lohit). This
# revision matches the lohit-ttf-20140220 release (Lohit-Devanagari 2.94.0).
SRC_URI = "git://github.com/pravins/lohit.git;branch=master;protocol=https"
SRCREV = "18c9c58c78029e6568c2e570f29e089201af5903"

PV = "2.94.0"

DEPENDS = "fontforge-native"

inherit allarch fontcache

FILES:${PN} += "${datadir}/fonts/truetype/*"

# Equivalent of the upstream apply_featurefile.py + generate.pe steps. The
# upstream apply_featurefile.py is Python 2 only, so do it inline in Python 3.
# Newer fontforge rejects comma separated lookupflags in the feature file.
do_compile() {
        sed -e '/lookupflag/ s/,/ /g' ${S}/devanagari/Lohit-Devanagari.fea > ${B}/Lohit-Devanagari-fixed.fea
        fontforge -lang=py -c '
import fontforge, sys
font = fontforge.open(sys.argv[1])
for lookup in font.gsub_lookups + font.gpos_lookups:
    font.removeLookup(lookup)
font.mergeFeature(sys.argv[2])
font.generate(sys.argv[3])
font.close()
' ${S}/devanagari/Lohit-Devanagari.sfd ${B}/Lohit-Devanagari-fixed.fea ${B}/Lohit-Devanagari.ttf
        # fontforge only warns on feature file errors, so make sure the
        # OpenType layout tables actually made it into the font.
        if ! grep -q -a GSUB ${B}/Lohit-Devanagari.ttf; then
                bbfatal "Lohit-Devanagari.ttf was generated without OpenType GSUB tables"
        fi
}

do_install() {
        install -d ${D}${datadir}/fonts/truetype/lohit-devanagari
        install -Dm 0644 ${B}/Lohit-Devanagari.ttf ${D}${datadir}/fonts/truetype/lohit-devanagari
}

ALLOW_EMPTY:${PN} = "1"
INHIBIT_DEFAULT_DEPS = "1"
