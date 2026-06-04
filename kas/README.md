# Kas Build Configurations

## Prerequisites

Install kas using pip:

```bash
pip install kas
```

### PolarFire SoC

```bash
cd meta-mchp/kas
export KAS_WORK_DIR=../../
KAS_MACHINE=mpfs-icicle-kit kas build polarfire-soc.yml --target mchp-base-image-sdk
```

### PIC64

```bash
cd meta-mchp/kas
export KAS_WORK_DIR=../../
KAS_MACHINE=pic64gx-curiosity-kit kas build pic64.yml --target mchp-base-image-sdk
```

### MPU

```bash
cd meta-mchp/kas
export KAS_WORK_DIR=../../
KAS_MACHINE=sam9x60-curiosity kas build mpu.yml --target mchp-base-image
```
