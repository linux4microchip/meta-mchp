# meta-mchp-mpu-bsp

## Description

This layer provides Board Support Package (BSP) and machine configurations for Microchip MPU evaluation boards for use with OpenEmbedded and/or Yocto Project.

## Layer Dependencies

This layer depends on:

```text
URI: git://github.com/linux4microchip/meta-mchp.git
layers: meta-mchp-common

URI: git://git.yoctoproject.org/meta-arm
layers: meta-arm-bsp, meta-arm-toolchain
```

## Supported Yocto Releases

This layer is compatible with the following Yocto Project releases:

- scarthgap

## Licensing

The contents of this layer are licensed under the MIT License. See COPYING.MIT for details.

## Contributing

If you want to contribute changes, you can send Github pull requests or patches at
**<https://github.com/linux4microchip/meta-mchp/pulls>**.

See [CONTRIBUTING.md](CONTRIBUTING.md) for additional information about
contribution guidelines.

## Maintainers

- Nicolas Ferre <nicolas.ferre@microchip.com>
- Dharma Balasubiramani <dharma.b@microchip.com>
