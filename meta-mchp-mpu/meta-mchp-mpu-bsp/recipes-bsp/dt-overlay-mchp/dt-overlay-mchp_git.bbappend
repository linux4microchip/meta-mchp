inherit mchp-compat-machines

# dm-verity: put the bundled kernel in the FIT instead of the bare zImage.

# The verity root hash rides in the initramfs, as /usr/share/misc/dm-verity.env
# INITRAMFS_IMAGE_BUNDLE = "1" bundles the kernel and initramfs.
# The default <machine>.its harcodes
#     data = /incbin/("./zImage");
# configure <machine.its> to bundle zImage and initramfs
# 	  data = /incbin/("zImage-initramfs-${MACHINE}.bin");

ITS_KERNEL_IMAGE ?= "zImage"
ITS_KERNEL_IMAGE_BUNDLED ?= "zImage-initramfs-${MACHINE}.bin"

do_compile:prepend:mchp-dm-verity () {
      its="${DT_MACHINE}.its"

      if [ ! -e "$its" ]; then
              bbfatal "$its not found; cannot point the FIT at the bundled kernel"
      fi

      if grep -q '/incbin/("./${ITS_KERNEL_IMAGE_BUNDLED}")' "$its"; then
              bbnote "$its already references ${ITS_KERNEL_IMAGE_BUNDLED}"
      elif grep -q '/incbin/("./${ITS_KERNEL_IMAGE}")' "$its"; then
              sed -i 's|/incbin/("./${ITS_KERNEL_IMAGE}")|/incbin/("./${ITS_KERNEL_IMAGE_BUNDLED}")|' "$its"
              bbnote "$its now bundles ${ITS_KERNEL_IMAGE_BUNDLED}"
      else
              bbfatal "$its references neither ./${ITS_KERNEL_IMAGE} nor ./${ITS_KERNEL_IMAGE_BUNDLED}: refusing to build a FIT with no initramfs (has the upstream .its renamed the kernel image?)"
      fi

      if [ ! -e "${DEPLOY_DIR_IMAGE}/${ITS_KERNEL_IMAGE_BUNDLED}" ]; then
              bbfatal "${DEPLOY_DIR_IMAGE}/${ITS_KERNEL_IMAGE_BUNDLED} is missing; INITRAMFS_IMAGE_BUNDLE must be 1 and virtual/kernel must have deployed the bundled image"
      fi
}

# Signs the FIT with mkimage below, so the keys have to exist first. The recipe
# only runs for dev keys; a production build supplies its own in
# UBOOT_SIGN_KEYDIR, matching the distro-layer u-boot and kernel appends.
DEPENDS:append:mchp-auth = " ${@bb.utils.contains('MCHP_DEV_SIGNING_KEYS', '1', 'dev-signing-keys-native', '', d)}"

do_compile:append:mchp-auth () {
    if [ -e "${DT_MACHINE}.its" ]; then
        bbnote "Injecting signature node into ${DT_MACHINE}.its"
        if ! grep -q "signature" "${DT_MACHINE}.its"; then
            sed -i '/fdt =/a \\t\t\tsignature {\n\t\t\t\talgo = "'${FIT_HASH_ALG}','${FIT_SIGN_ALG}'";\n\t\t\t\tkey-name-hint = "'${UBOOT_SIGN_KEYNAME}'";\n\t\t\t\tsign-images = "fdt", "kernel";\n\t\t\t};' "${DT_MACHINE}.its"
        fi

        # mkimage takes the directory and looks for ${UBOOT_SIGN_KEYNAME}.key/.crt
        # inside it. With MCHP_DEV_SIGNING_KEYS = "0" nothing generates those, so
        # check here rather than letting mkimage fail on a missing key.
        for f in "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.key" \
                 "${UBOOT_SIGN_KEYDIR}/${UBOOT_SIGN_KEYNAME}.crt"; do
            if [ ! -f "$f" ]; then
                bbfatal "Authentication boot file check, missing: $f. Provide your signing keys in UBOOT_SIGN_KEYDIR or set MCHP_DEV_SIGNING_KEYS = \"1\" to generate development keys."
            fi
        done

        bbnote "Signing ${DT_MACHINE}.itb FIT image with mchp-auth keys"
        DTC_OPTIONS="-Wno-unit_address_vs_reg -Wno-graph_child_address -Wno-pwms_property"
        mkimage -k ${UBOOT_SIGN_KEYDIR} -D "-i${DEPLOY_DIR_IMAGE} -p 2000 ${DTC_OPTIONS}" -f ${DT_MACHINE}.its ${DT_MACHINE}.itb
    fi
}
