do_compile:append() {
    install -d "${HSS_SIGN_KEYDIR}"

    if [ ! -f "${HSS_SIGN_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem" ]; then
        bbwarn "dev-signing-keys-native: Generating DEV ECDSA HSS payload signing keys in ${HSS_SIGN_KEYDIR}."
        openssl ecparam -genkey -name secp384r1 -param_enc named_curve \
            -out "${HSS_SIGN_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem"
        openssl ec -in "${HSS_SIGN_KEYDIR}/${HSS_PAYLOAD_PRIVATE_KEYNAME}.pem" \
            -pubout -out "${HSS_SIGN_KEYDIR}/${HSS_PAYLOAD_PUBLIC_KEYNAME}.der" -outform DER
    fi
    bbwarn "dev-signing-keys-native: These keys are NOT suitable for production use."
    bbwarn "dev-signing-keys-native: To use your own keys, please read the Security Features section of the readme"
}
do_compile[vardeps] += "HSS_PAYLOAD_PRIVATE_KEYNAME HSS_PAYLOAD_PUBLIC_KEYNAME HSS_SIGN_KEYDIR"
