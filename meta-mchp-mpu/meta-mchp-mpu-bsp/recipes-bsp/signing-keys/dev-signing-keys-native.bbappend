# Second tier of the certificate chain the SoC ROM code walks when it
# authenticates at91bootstrap. Only the MPU ROM code has that stage, so the tier
# is added here instead of in the common recipe.
#
# Not gated on :mchp-auth. native.bbclass runs DISTRO_FEATURES through
# class_filter_features, which keeps only DISTRO_FEATURES_NATIVE plus the few
# names in DISTRO_FEATURES_FILTER_NATIVE, so mchp-auth is stripped and never
# reaches DISTROOVERRIDES for a native recipe. Presence of this layer in
# BBLAYERS is the gate, as it is for the pic64 and polarfire-soc appends, which
# use a bare do_compile:append for the same reason. The recipe is only pulled in
# by mchp-auth builds via the u-boot, kernel and dt-overlay appends.
#
#   ${UBOOT_SIGN_KEYNAME}.key/.crt    root of trust, issued by the base recipe.
#                                     Signs the FIT, and is the root of this
#                                     chain.
#   ${MCHP_ROMCODE_SIGN_KEYNAME}.key  boot signing key, the second tier, with
#                             .csr    the request to have it certified and the
#                             .crt    certificate the root issues for it here.
#
# Two tiers because that is the model the boards ship under: only the root is
# pinned in the device, so a compromised or expired signing key is replaced by
# issuing a new certificate under the same root, and the payload programmed into
# the device stays valid. The .csr is kept so that in production the same
# request can go to a real signing authority instead.
#
# MCHP_ROMCODE_SIGN_KEYNAME is set in mchp-auth.inc.

do_compile:append() {
    if [ ! -f "${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.key" ]; then
        bbwarn "dev-signing-keys-native: Generating DEV RSA ROM code boot signing keys in ${UBOOT_SIGN_KEYDIR}."

        # 'openssl x509 -req' adds no extensions of its own, unlike 'openssl req
        # -x509' (which is why the root certificate the base recipe produces
        # already carries basicConstraints CA:TRUE), so the X.509v3 extensions
        # for this tier are supplied here. CA:TRUE so the ROM code accepts the
        # certificate as an issuer while walking the chain, and
        # keyCertSign/digitalSignature for the signing role. Adjust here if the
        # ROM code validates particular extension values.
        cat > "${B}/v3.ext" <<EOF
basicConstraints = CA:TRUE
keyUsage = digitalSignature, keyCertSign
subjectKeyIdentifier = hash
authorityKeyIdentifier = keyid,issuer
EOF

        openssl genrsa -F4 \
            -out "${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.key" 4096

        openssl req -batch -new -sha256 \
            -key "${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.key" \
            -out "${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.csr" \
            -subj "/O=Microchip Technology/CN=${UBOOT_SIGN_KEYNAME} boot signing"

        openssl x509 -req -sha256 -days 2922 -set_serial 0x1234 \
            -extfile "${B}/v3.ext" \
            -in "${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.csr" \
            -CA "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt" \
            -CAkey "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" \
            -out "${UBOOT_SIGN_KEYDIR}/${MCHP_ROMCODE_SIGN_KEYNAME}.crt"
    fi

    bbwarn "dev-signing-keys-native: These keys are NOT suitable for production use."
    bbwarn "dev-signing-keys-native: To use your own keys, please read the Security Features section of the readme"
}
do_compile[vardeps] += "MCHP_ROMCODE_SIGN_KEYNAME"
