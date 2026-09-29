# UBI volume layout for dm-verity NAND
#
# oe-core's write_ubi_config() (image_types.bbclass) generates a single
# autoresize volume holding ${UBI_IMGTYPE}. But mpu needs 2 volumes.
#
# vol 0 ${UBI_VOLNAME}            The ${UBI_IMGTYPE} image, i.e. verity data +
#                                 appended hash tree. ubi exposes this as
#                                 ubi0_0 and initramfs runs veritysetup on that.
#
# vol 1 ${MCHP_UBI_DATA_VOLNAME}  RW ubifs holding upper workdirs of the /etc/
#                                 overlay.
#
# Only reached when mchp-dm-verity is enabled: The machine conf adds this class
# via IMAGE_CLASSES:append:mchp-dm-verity. image.bbclass inherits IMAGE_CLASSES
# after image_types (image.bbclass: IMGCLASSES). So the definition below
# replaces the oe-core one.

MCHP_UBI_DATA_VOLNAME ?= "data"

# The FIT carries the verity roothash in the bundled initramfs.
# mchp-dm-verity.inc drops the FIT recipe from MACHINE_ESSENTIAL_EXTRA_RDEPENDS
# to break rootfs -> initramfs -> kernel -> FIT -> rootfs circular dependency.
# On SD do_image_wic pulls it. For NAND pull it back from do_image_ubi
do_image_ubi[depends] += "${DM_VERITY_FIT_RECIPE}:do_deploy"

# Overwrite ubi config
write_ubi_config() {
	local vname="$1"
	local rootfs_img="${IMGDEPLOYDIR}/${IMAGE_NAME}$vname.${UBI_IMGTYPE}"
	local data_img="${WORKDIR}/mchp-ubi-data$vname.ubifs"
	local data_dir="${WORKDIR}/mchp-ubi-data$vname.content"

	if [ ! -f "$rootfs_img" ]; then
		bbfatal "mchp-ubi-verity: $rootfs_img does not exist." \
			"UBI_IMGTYPE is '${UBI_IMGTYPE}' - it must name the verity" \
			"image type so that IMAGE_TYPEDEP:ubi builds it."
	fi

	# A UBI image may carry one autoresize volume, so the read-only rootfs takes
	# an explicit size (ubinize rounds up to a LEB multiple) and the RW data
	# volume absorbs the rest of the MTD partition.
	local rootfs_size=$(stat -Lc '%s' "$rootfs_img")

	# ubinize reserves space for a volume but does not format it, and mounting
	# an unformatted volume fails. overlayfs-etc's preinit only warns on a
	# failed mount and carries on. Format it here. MKUBIFS_ARGS and UBINIZE_ARGS
	# read from machine conf
	rm -rf "$data_dir"
	mkdir -p "$data_dir"
	mkfs.ubifs -r "$data_dir" -o "$data_img" ${MKUBIFS_ARGS}

	cat <<EOF > ubinize$vname-${IMAGE_NAME}.cfg
[rootfs]
mode=ubi
image=$rootfs_img
vol_id=0
vol_type=${UBI_VOLTYPE}
vol_name=${UBI_VOLNAME}
vol_size=$rootfs_size

[data]
mode=ubi
image=$data_img
vol_id=1
vol_type=dynamic
vol_name=${MCHP_UBI_DATA_VOLNAME}
vol_flags=autoresize
EOF
}
