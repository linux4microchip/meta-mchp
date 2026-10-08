SUMMARY = "Initial bootstrap for AT91 ARM MPUs"
DESCRIPTION = "\
    at91bootstrap is the second-level bootloader for Microchip \
    AT91 SoCs. It provides a set of algorithms to manage the   \
    hardware initialization and to download the main           \
    application (or a third-level bootloader) from specified   \
    boot media to main memory and start it.                    \
"
AUTHOR = "Microchip Technology"
HOMEPAGE = "https://www.linux4sam.org/bin/view/Linux4SAM/AT91Bootstrap"
BUGTRACKER = "https://github.com/linux4sam/at91bootstrap/issues"
SECTION = "bootloaders"

inherit cml1 deploy

DEPENDS += "bc-native python3-native sam-ba-native"

AT91BOOTSTRAP_MACHINE = "${DT_MACHINE}"

AT91BOOTSTRAP_CONFIG ??= "${AT91BOOTSTRAP_MACHINE}nf_uboot"
AT91BOOTSTRAP_CONFIG:sama5d3-xplained-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sama5d4-xplained ??= "${AT91BOOTSTRAP_MACHINE}nf_uboot_secure"
AT91BOOTSTRAP_CONFIG:sama5d4-xplained-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot_secure"
AT91BOOTSTRAP_CONFIG:sama5d2-xplained ??= "${AT91BOOTSTRAP_MACHINE}-bsrdf_uboot"
AT91BOOTSTRAP_CONFIG:sama5d2-xplained-emmc ??= "${AT91BOOTSTRAP_MACHINE}emmc_uboot"
AT91BOOTSTRAP_CONFIG:sama5d2-xplained-sd ??= "${AT91BOOTSTRAP_MACHINE}-bsrsd_uboot"
AT91BOOTSTRAP_CONFIG:sama5d2-ptc-ek-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sama5d27-som1-ek ??= "${AT91BOOTSTRAP_MACHINE}qspi_uboot"
AT91BOOTSTRAP_CONFIG:sama5d27-som1-ek-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sama5d27-som1-ek-optee-sd ??= "${AT91BOOTSTRAP_MACHINE}-opteesd_uboot"
AT91BOOTSTRAP_CONFIG:sama5d27-wlsom1-ek-sd ??= "${AT91BOOTSTRAP_MACHINE}-bsrsd_uboot"
AT91BOOTSTRAP_CONFIG:sama5d29-curiosity-sd ??= "${AT91BOOTSTRAP_MACHINE}-bsrsd_uboot"
AT91BOOTSTRAP_CONFIG:sama5d2-icp-sd ??= "${AT91BOOTSTRAP_MACHINE}-bsrsd_uboot"
AT91BOOTSTRAP_CONFIG:sam9x60ek ??= "${AT91BOOTSTRAP_MACHINE}nf_uboot"
AT91BOOTSTRAP_CONFIG:sam9x60ek-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sama7g5ek-sd ??= "${AT91BOOTSTRAP_MACHINE}-bsrsd_uboot"
AT91BOOTSTRAP_CONFIG:sama7g5ek-optee-sd ??= "${AT91BOOTSTRAP_MACHINE}-opteesd_uboot"
AT91BOOTSTRAP_CONFIG:sama7g5ek-emmc ??= "${AT91BOOTSTRAP_MACHINE}-bsremmc_uboot"
AT91BOOTSTRAP_CONFIG:sama7g5ek-ospi ??= "${AT91BOOTSTRAP_MACHINE}df_qspi_uboot"
AT91BOOTSTRAP_CONFIG:sama7g54-curiosity-pro-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sam9x60-curiosity-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sam9x60-curiosity-pro-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sam9x75-curiosity-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sam9x75-curiosity-pro-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sam9x75eb-sd ??= "${AT91BOOTSTRAP_MACHINE}sd_uboot"
AT91BOOTSTRAP_CONFIG:sama7d65-curiosity-sd ??= "${AT91BOOTSTRAP_MACHINE}-bsrsd1_uboot"
AT91BOOTSTRAP_CONFIG:sama7d65-curiosity-pro-sd ??= "${AT91BOOTSTRAP_MACHINE}-bsrsd1_uboot"

AT91BOOTSTRAP_TARGET ??= "${AT91BOOTSTRAP_CONFIG}_defconfig"
AT91BOOTSTRAP_LOAD ??= "nandflashboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d2-xplained ??= "dataflashboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d2-xplained-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d27-ptc-ek-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d27-som1-ek ??= "qspiboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d27-som1-ek-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d27-som1-ek-optee-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d27-wlsom1-ek-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d29-curiosity-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d3-xplained-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d4-xplained-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama5d2-icp-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sam9x60ek-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama7g5ek-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama7g5ek-optee-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama7g5ek-emmc ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama7g5ek-ospi ??= "dataflashboot-uboot"
AT91BOOTSTRAP_LOAD:sama7g54-curiosity-pro-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sam9x60-curiosity-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sam9x60-curiosity-pro-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sam9x75-curiosity-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sam9x75-curiosity-pro-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sam9x75eb-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama7d65-curiosity-sd ??= "sdboot-uboot"
AT91BOOTSTRAP_LOAD:sama7d65-curiosity-pro-sd ??= "sdboot-uboot"

AT91BOOTSTRAP_SUFFIX ?= "bin"
AT91BOOTSTRAP_IMAGE ?= "${AT91BOOTSTRAP_MACHINE}-${AT91BOOTSTRAP_LOAD}-${PV}.${AT91BOOTSTRAP_SUFFIX}"
AT91BOOTSTRAP_BINARY ?= "at91bootstrap.${AT91BOOTSTRAP_SUFFIX}"
AT91BOOTSTRAP_SYMLINK ?= "at91bootstrap-${AT91BOOTSTRAP_MACHINE}.${AT91BOOTSTRAP_SUFFIX}"

do_configure() {
    # Copy board defconfig to .config if .config does not exist. This
    # allows recipes to manage the .config themselves in
    # do_configure:prepend().
    if [ -f "${AT91BOOTSTRAP_CONFIG_PATH}/${AT91BOOTSTRAP_TARGET}" ] && [ ! -f "${B}/.config" ]; then
        cp "${AT91BOOTSTRAP_CONFIG_PATH}/${AT91BOOTSTRAP_TARGET}" "${B}/.config"
    fi

    # Copy defconfig to .config if .config does not exist. This allows
    # recipes to manage the .config themselves in do_configure:prepend()
    # and to override default settings with a custom file.
    if [ -f "${WORKDIR}/defconfig" ] && [ ! -f "${B}/.config" ]; then
        cp "${WORKDIR}/defconfig" "${B}/.config"
    fi

    if [ ! -f "${S}/.config" ]; then
        bbfatal "No config files found"
    fi

    cml1_do_configure
}

do_compile() {
    if [ "${@bb.utils.contains('DISTRO_FEATURES', 'ld-is-gold', 'ld-is-gold', '', d)}" = "ld-is-gold" ] ; then
        sed -i 's/$(CROSS_COMPILE)ld$/$(CROSS_COMPILE)ld.bfd/g' ${S}/Makefile
    fi

    unset CFLAGS CPPFLAGS LDFLAGS
    oe_runmake
}

do_deploy () {
    install -d ${DEPLOYDIR}
    install ${AT91BOOTSTRAP_BIN_PATH}/${AT91BOOTSTRAP_BINARY} ${DEPLOYDIR}/${AT91BOOTSTRAP_IMAGE}

    cd ${DEPLOYDIR}
    rm -f ${AT91BOOTSTRAP_BINARY} ${AT91BOOTSTRAP_SYMLINK}
    ln -sf ${AT91BOOTSTRAP_IMAGE} ${AT91BOOTSTRAP_SYMLINK}
    ln -sf ${AT91BOOTSTRAP_IMAGE} ${AT91BOOTSTRAP_BINARY}

    # Create a symlink ready for file copy on SD card
    rm -f boot.bin BOOT.BIN
    ln -sf ${AT91BOOTSTRAP_IMAGE} BOOT.BIN
}
addtask deploy before do_build after do_compile

PACKAGE_ARCH = "${MACHINE_ARCH}"

TOOLCHAIN = "gcc"

# Enable secureboot configs in at91bootstrap. It CMAC verifies u-boot.cip,
# compiles CMAC/IV/Cipher keys into itself. Thise keys need to be matched with
# which the u-boot.cip is encrypted and signed. u-boot.cip is generated with
# sam_genimage.py which is part of secure sam-ba cipher package. This is done
# only when mchp-auth distro feature is enabled.

# u-boot.bin must be deployed before we can wrap it into u-boot.cip.
do_deploy[depends] += "${@bb.utils.contains('DISTRO_FEATURES', 'mchp-auth', 'u-boot-mchp:do_deploy', '', d)}"

# sam_genimage.py part of secure SAM-BA cipher suite, which is a
# host-prerequisite. Make it available in the PATH.
SAM_SECURE_TOOLS_DIR ??= "/opt/secure_sam_ba_cipher-3.9.0"
PATH:prepend:mchp-auth = "${SAM_SECURE_TOOLS_DIR}:"

SECURE_BOOT_KEYFILE = "${B}/mchp-secure-boot.keys"

# Every key, certificate, signing request and tool configuration the secure boot
# chain produces is collected in MCHP_SECURE_DEPLOY_SUBDIR.
MCHP_SECURE_DEPLOY_SUBDIR ?= "secure-boot"
MCHP_SECURE_DEPLOYDIR = "${DEPLOYDIR}/${MCHP_SECURE_DEPLOY_SUBDIR}"

do_configure:append:mchp-auth () {
    # Generate the AES keys once and keep it in the file so that do_deploy
    # signs u-boot with the exact same keys which are built into at91bootstrap.
    # Each word is a random 4-byte value: 8 words for the 256-bit cipher key, 4
    # for the IV, 8 for the 256-bit CMAC key.

    rm -f "${SECURE_BOOT_KEYFILE}.tmp"
    for w in 0 1 2 3 4 5 6 7; do
        echo "AES_CIPHER_KEY_WORD${w}=$(od -An -N4 -tx1 /dev/urandom | tr -d ' \n')" >> "${SECURE_BOOT_KEYFILE}.tmp"
    done
    for w in 0 1 2 3; do
        echo "AES_IV_WORD${w}=$(od -An -N4 -tx1 /dev/urandom | tr -d ' \n')" >> "${SECURE_BOOT_KEYFILE}.tmp"
    done
    for w in 0 1 2 3 4 5 6 7; do
        echo "AES_CMAC_KEY_WORD${w}=$(od -An -N4 -tx1 /dev/urandom | tr -d ' \n')" >> "${SECURE_BOOT_KEYFILE}.tmp"
    done
    mv "${SECURE_BOOT_KEYFILE}.tmp" "${SECURE_BOOT_KEYFILE}"

    # Replace (or add) a symbol in the .config that cml1_do_configure produced.
    kcfg_set() {
        sed -i "\%^$1=%d; \%^# $1 is not set%d" "${B}/.config"
        echo "$1=$2" >> "${B}/.config"
    }

    kcfg_set CONFIG_SECURE y
    kcfg_set CONFIG_AES_KEY_SIZE_256 y
    kcfg_set CONFIG_IMAGE_NAME '"u-boot.cip"'

    while IFS='=' read -r sym val; do
        kcfg_set "CONFIG_${sym}" "0x${val}"
    done < "${SECURE_BOOT_KEYFILE}"

    # Update the new symbols added.
    yes '' | oe_runmake oldconfig

    if ! grep -q '^CONFIG_SECURE=y' "${B}/.config"; then
        bbfatal "at91bootstrap: CONFIG_SECURE could not be enabled for ${MACHINE} (missing CPU_HAS_AES?); mchp-auth secure boot is not supported on this board"
    fi
}

do_deploy:append:mchp-auth () {
    if [ ! -f "${SECURE_BOOT_KEYFILE}" ]; then
        bbfatal "at91bootstrap: ${SECURE_BOOT_KEYFILE} missing; do_configure must run before do_deploy"
    fi

    cipher_key=""; iv=""; cmac_key=""
    while IFS='=' read -r sym val; do
        case "${sym}" in
            AES_CIPHER_KEY_WORD*) cipher_key="${cipher_key}${val}" ;;
            AES_IV_WORD*)         iv="${iv}${val}" ;;
            AES_CMAC_KEY_WORD*)   cmac_key="${cmac_key}${val}" ;;
        esac
    done < "${SECURE_BOOT_KEYFILE}"

    # application.yml is used to sign+encrypt the u-boot.
    cat > "${B}/application.yaml" <<EOF
chip_type: application
image_type: secure
security:
  signature:
    type: CMAC_AES
    key_data: data:${cmac_key}
  cipher:
    type: AES
    key_data: data:${cipher_key}
    iv_data: data:${iv}
specifics:
    header: True
EOF

    if [ ! -e "${DEPLOY_DIR_IMAGE}/u-boot.bin" ]; then
        bbfatal "at91bootstrap: ${DEPLOY_DIR_IMAGE}/u-boot.bin not found; cannot generate u-boot.cip"
    fi
    cp -f "${DEPLOY_DIR_IMAGE}/u-boot.bin" "${B}/u-boot.bin"

    if ! command -v sam_genimage.py >/dev/null 2>&1; then
        bbfatal "at91bootstrap: sam_genimage.py not found in ${SAM_SECURE_TOOLS_DIR}."
    fi

    bbnote "Generating encrypted/signed u-boot.cip for secure boot"
    ( cd "${B}" && sam_genimage.py -c application.yaml u-boot.bin u-boot.cip )

    install -m 0644 "${B}/u-boot.cip" "${DEPLOYDIR}/u-boot.cip"

    # The AES words compiled into at91bootstrap for this stage, and the
    # configuration that encrypted u-boot with them. Both are needed to
    # reproduce or check u-boot.cip against the running bootstrap.
    install -d "${MCHP_SECURE_DEPLOYDIR}"
    install -m 0600 "${SECURE_BOOT_KEYFILE}" "${MCHP_SECURE_DEPLOYDIR}/"
    install -m 0600 "${B}/application.yaml" "${MCHP_SECURE_DEPLOYDIR}/"
}

# ROM code authentication of at91bootstrap. Applies only when mchp-auth distro
# enabled.The SoC ROM code authenticates and decrypts at91bootstrap itself.
#
#   boot.cip                     at91bootstrap, RSA signed and AES encrypted.
#                                Stays at the top of the deploy dir because
#                                BOOT.BIN points at it.
#   secure-boot/customer-key.cip the matching key payload, programmed into the
#                                device once.
#
# Everything else the stage produces - the chain, the signing key and its
# request, the AES words and the tool configuration - lands in that same
# secure-boot/ directory (MCHP_SECURE_DEPLOYDIR above).
#
# The certificate chain is deliberately two levels, because that is the model
# the boards are shipped under: the board owner generates a signing key and
# raises a certificate signing request, the signing authority certifies it with
# the root key, and the board owner gets the signed certificate back. Only the
# root is pinned in the device, so a signing key can be replaced by issuing a
# new certificate under the same root.
#
# The root CA is the key pair dev-signing-keys-native already generates for FIT
# signing, reused here under its own names (${UBOOT_SIGN_KEYNAME}.key/.crt).

DEPENDS:append:mchp-auth = " openssl-native"

# The chain is only generated for dev keys; a production build supplies its own
# in UBOOT_SIGN_KEYDIR, as the distro-layer u-boot and kernel appends do.
DEPENDS:append:mchp-auth = " ${@bb.utils.contains('MCHP_DEV_SIGNING_KEYS', '1', 'dev-signing-keys-native', '', d)}"

# Run as a postfunc rather than an append: this has to be the last thing that
# touches BOOT.BIN, and do_deploy:append:sama7d65 in at91bootstrap_4.0.13.bb
# also reinstalls the image and recreates that symlink.
do_deploy[postfuncs] += "${@bb.utils.contains('DISTRO_FEATURES', 'mchp-auth', 'at91bootstrap_romcode_sign', '', d)}"

# MCHP_ROMCODE_SIGN_KEYNAME names the signing tier. It is set in mchp-auth.inc
# because dev-signing-keys-native has to agree with this recipe on the name.

# Certificate returned by the signing authority for MCHP_ROMCODE_SIGN_KEYNAME.csr.
MCHP_SECURE_SIGNING_CERT ?= ""

# ROM public key the customer key payload is encrypted to. Part of secure
# SAM-BA cipher suite named after the chip, and MCHP_SECURE_CHIP_TYPE
#
#   sam9x70  -> ${SAM_SECURE_TOOLS_DIR}/sam9x70_public_key.pem sama7d65 ->
#   ${SAM_SECURE_TOOLS_DIR}/sama7d65_public_key.pem

MCHP_SECURE_ROM_PUBKEY ?= "${SAM_SECURE_TOOLS_DIR}/${MCHP_SECURE_CHIP_TYPE}_public_key.pem"

MCHP_ROMCODE_KEYFILE = "${B}/mchp-romcode.keys"

at91bootstrap_romcode_sign () {
    if [ -z "${MCHP_SECURE_CHIP_TYPE}" ]; then
        bbfatal "at91bootstrap: MCHP_SECURE_CHIP_TYPE is empty for ${MACHINE}"
    fi

    if [ -z "${MCHP_SECURE_ROM_PUBKEY}" ]; then
        bbfatal "at91bootstrap: MCHP_SECURE_ROM_PUBKEY has been set empty; leave it unset to take the ROM public key for ${MCHP_SECURE_CHIP_TYPE} from ${SAM_SECURE_TOOLS_DIR}, or point it at the key to use"
    fi

    if [ ! -f "${MCHP_SECURE_ROM_PUBKEY}" ]; then
        bbfatal "at91bootstrap: ROM public key not found: ${MCHP_SECURE_ROM_PUBKEY}."
    fi

    for tool in sam_gen_keypayload.py sam_genimage.py; do
        if ! command -v "$tool" >/dev/null 2>&1; then
            bbfatal "at91bootstrap: $tool not found on PATH; it is required to authenticate at91bootstrap for mchp-auth secure boot"
        fi
    done

    if [ -z "${MCHP_ROMCODE_SIGN_KEYNAME}" ]; then
        bbfatal "at91bootstrap: MCHP_ROMCODE_SIGN_KEYNAME is empty"
    fi

    ca_key="${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key"
    ca_crt="${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt"
    sign_key="${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.key"
    sign_crt="${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.crt"
    # The request is not used to issue anything here, only linked into
    # secure-boot/ so it can be submitted; checked so that link cannot dangle.
    sign_csr="${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.csr"
    for f in "$ca_key" "$ca_crt" "$sign_key" "$sign_crt" "$sign_csr"; do
        if [ ! -f "$f" ]; then
            bbfatal "at91bootstrap: chain file missing: $f (expected from dev-signing-keys-native, or from your own keys in UBOOT_SIGN_KEYDIR)"
        fi
    done

    # AES material for the ROM code stage: a 256 bit cipher key, a 128 bit IV
    # and a 256 bit CMAC key. Separate from the AES words compiled into
    # at91bootstrap for the u-boot stage. Both the key payload programmed into
    # the device and the encrypted image are produced from these values in this
    # one task, so minting them here keeps the two in agreement.
    {
        echo "CIPHER_KEY=$(od -An -N32 -tx1 /dev/urandom | tr -d ' \n')"
        echo "IV=$(od -An -N16 -tx1 /dev/urandom | tr -d ' \n')"
        echo "TAG_KEY=$(od -An -N32 -tx1 /dev/urandom | tr -d ' \n')"
    } > "${MCHP_ROMCODE_KEYFILE}.tmp"
    mv "${MCHP_ROMCODE_KEYFILE}.tmp" "${MCHP_ROMCODE_KEYFILE}"
    . "${MCHP_ROMCODE_KEYFILE}"

    cd "${B}"


    # The certs in DER form is needed by ROM Code secrure boot chain
    openssl x509 -in "$ca_crt" -outform DER -out "${UBOOT_SIGN_KEYNAME}.der"
    openssl x509 -in "$sign_crt" -outform DER -out "${MCHP_ROMCODE_SIGN_KEYNAME}.der"

    install -m 0600 "$sign_key" "${MCHP_ROMCODE_SIGN_KEYNAME}.key"
    install -m 0644 "$sign_crt" "${MCHP_ROMCODE_SIGN_KEYNAME}.crt"

    cat > cust_RSA.yaml <<EOF
chip_type: ${MCHP_SECURE_CHIP_TYPE}
image_type: secure
security:
  signature:
    type: RSA
    key_data: file:${MCHP_ROMCODE_SIGN_KEYNAME}.key
    certificates: [ file:${UBOOT_SIGN_KEYNAME}.der, file:${MCHP_ROMCODE_SIGN_KEYNAME}.der ]
  cipher:
    type: AES
    key_data: data:$CIPHER_KEY
    iv_data: data:$IV
  tag:
    type: CMAC_AES
    key_data: data:$TAG_KEY
EOF

    bbnote "Generating customer key payload for ${MCHP_SECURE_CHIP_TYPE}"
    rm -f customer-key.cip customer-key_*.cip

    # Handling different version of secure sam-ba cipher package
    if sam_gen_keypayload.py --help 2>&1 | grep -q -- '--key_file'; then
        keycfg_opt="-k"
    else
        keycfg_opt="-c"
    fi

    # Generate the customer key to be flashed into OTP or test though emulaiton
    # mode
    sam_gen_keypayload.py -d "${MCHP_SECURE_ROM_PUBKEY}" $keycfg_opt cust_RSA.yaml -o customer-key.cip
    if [ ! -f customer-key.cip ]; then
        mv customer-key_*.cip customer-key.cip
    fi

    bbnote "Signing and encrypting at91bootstrap into boot.cip"
    cp -f "${DEPLOYDIR}/${AT91BOOTSTRAP_IMAGE}" boot.bin
    sam_genimage.py -c cust_RSA.yaml boot.bin boot.cip

    install -m 0644 boot.cip "${DEPLOYDIR}/boot.cip"

    # Install all keys to MCHP_SECURE_DEPLOYDIR
    install -d "${MCHP_SECURE_DEPLOYDIR}"
    install -m 0644 "${UBOOT_SIGN_KEYNAME}.der" "${MCHP_ROMCODE_SIGN_KEYNAME}.der" \
        "${MCHP_ROMCODE_SIGN_KEYNAME}.crt" "${MCHP_SECURE_DEPLOYDIR}/"
    install -m 0600 "${MCHP_ROMCODE_KEYFILE}" cust_RSA.yaml "${MCHP_SECURE_DEPLOYDIR}/"
    install -m 0644 customer-key.cip "${MCHP_SECURE_DEPLOYDIR}/customer-key.cip"

    for f in "${UBOOT_SIGN_KEYNAME}.key" "${UBOOT_SIGN_KEYNAME}.crt" \
             "${MCHP_ROMCODE_SIGN_KEYNAME}.key" "${MCHP_ROMCODE_SIGN_KEYNAME}.csr"; do
        if [ "${UBOOT_SIGN_KEYDIR}" = "${DEPLOY_DIR_IMAGE}" ]; then
            ln -sfn "../$f" "${MCHP_SECURE_DEPLOYDIR}/$f"
        else
            ln -sfn "${UBOOT_SIGN_KEYDIR}/$f" "${MCHP_SECURE_DEPLOYDIR}/$f"
        fi
    done

}
