#!/bin/sh

set -e

ABOOTIMG=${ABOOTIMG:-$(which abootimg || true)}

if [ -z "${ABOOTIMG}" ]; then
  echo "abootimg not found. Please install abootimg." >&2
  exit 1
fi

KERNEL_DIR=$(dirname "$0")
KERNEL_OUT=${KERNEL_OUT:-$(readlink -f "${KERNEL_DIR}/../KERNEL_OBJ")}
KERNEL_ARCH=arm64
KERNEL_DEFCONFIG=${KERNEL_DEFCONFIG:-bq_aquaris_m10_FHD_ubuntu_defconfig}
KERNEL_CROSS_COMPILE=${KERNEL_CROSS_COMPILE:-$(readlink -f "${KERNEL_DIR}/../cit-aarch64-linux-android-4.9")/bin/aarch64-linux-android-}

mkdir -p "${KERNEL_OUT}"
make -C "${KERNEL_DIR}" -j $(nproc) O="${KERNEL_OUT}" ARCH=${KERNEL_ARCH} CROSS_COMPILE="${KERNEL_CROSS_COMPILE}" ${KERNEL_DEFCONFIG} $@ \
  && make -C "${KERNEL_DIR}" -j $(nproc) O="${KERNEL_OUT}" ARCH=${KERNEL_ARCH} CROSS_COMPILE="${KERNEL_CROSS_COMPILE}" $@ \
  && cp "${KERNEL_DIR}/boot.img" "${KERNEL_OUT}/boot.img" \
  && abootimg -u "${KERNEL_OUT}/boot.img" -k "${KERNEL_OUT}/arch/arm64/boot/Image.gz-dtb"
