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
