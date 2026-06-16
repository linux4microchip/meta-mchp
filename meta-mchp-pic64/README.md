# meta-mchp-pic64

## Description

This layer provides Board Support Package (BSP) and machine configurations for Microchip PIC64 evaluation kits for use with OpenEmbedded and/or Yocto Project.

## Supported Machines

| `MACHINE`                                 | Board Name                         | Description                                                        |
| ------------------------------------------|------------------------------------|--------------------------------------------------------------------|
| `MACHINE=pic64gx-curiosity-kit`           | PIC64GX Curiosity Kit              | PIC64GX Curiosity Kit                                              |
| `MACHINE=pic64gx-curiosity-kit-amp`       | PIC64GX Curiosity Kit              | PIC64GX Curiosity Kit in Asymmetric Multiprocessing (AMP) mode     |

The `pic64gx-curiosity-kit-amp` machine can be used to build the PIC64GX Curiosity kit with AMP support. Please see the [Asymmetric Multiprocessing (AMP)](https://mi-v-ecosystem.github.io/redirects/asymmetric-multiprocessing_amp) documentation for further details.

## Image Targets

The table below describes some custom Microchip image targets that can be used to run various demos, as well as recommended
standard OpenEmbedded image targets. For additional standard OpenEmbedded images, please refer to the
[OpenEmbedded documentation](https://docs.yoctoproject.org/dev/ref-manual/images.html#images).

| `Image`                       | Description                                                                                    |
| ----------------------------- | ---------------------------------------------------------------------------------------------- |
| `core-image-minimal`          | A small image just capable of allowing a device to boot                                        |
| `mchp-base-image`             | A Microchip base image with standard Linux utilities, as well as some Microchip apps and examples             |
| `mchp-base-image-sdk`         | A Microchip base image with additional support for software development, including toolchains and debug tools |

> [!IMPORTANT]
Login with root account, there is no password set.

## Build Instructions

Please see the meta-mchp-common [README](https://github.com/linux4microchip/meta-mchp/blob/scarthgap/meta-mchp-common/README.md) section for detailed steps on how to setup and start a build for any of the supported devices.

## Deploy Instructions

### Copying a Disk Image to a SD card

1. **Recommended Tool:** Use `bmaptool` to write the disk image to your storage device. It's faster than traditional tools like `dd` or `cp`.

2. **Find the Image:**
   The disk image (a `.wic` file) is in `yocto-dev/build/tmp-glibc/deploy/images/<MACHINE>/`.
   Example:
   `yocto-dev/build/tmp-glibc/deploy/images/pic64gx-curiosity-kit/mchp-base-image-pic64gx-curiosity-kit.wic`

3. **Prepare the Target Storage Device**
   SD card can be programmed as follows:
      - Insert an SD card or microSD card into the host computer using an SD card reader.

4. **Flash the Image:**

     ```sh
     sudo bmaptool copy tmp-glibc/deploy/images/pic64gx-curiosity-kit/mchp-base-image-pic64gx-curiosity-kit.rootfs.wic /dev/sdX
     ```

      - **Important:**
      Double-check the device name (`/dev/sdX`) using `dmesg`, `lsblk`, or GNOME Disks to avoid overwriting your system disk.

## Layer Dependencies

This layer depends on:

```text
URI: git://git.openembedded.org/openembedded-core
layers: meta

URI: git://git.yoctoproject.org/meta-openembedded
layers: meta-oe, meta-python, meta-multimedia, meta-networking

URI: git://github.com/linux4microchip/meta-mchp.git
layers: meta-mchp-common
```

## Supported Yocto Releases

This layer is compatible with the following Yocto Project releases:

- scarthgap

## Licensing

The contents of this layer are licensed under the MIT License. See COPYING.MIT for details.

## Contributing

If you want to contribute changes, you can send Github pull requests or patches at
**<https://github.com/linux4microchip/meta-mchp/pulls>**.

See [CONTRIBUTING.md](../CONTRIBUTING.md) for additional information about
contribution guidelines.

## Maintainers

- Valentina Fernandez Alanis <valentina.fernandezalanis@microchip.com>
