#!/bin/sh

set -e

KERNEL_DIR=$(dirname "$0")
KERNEL_OUT=${KERNEL_OUT:-$(readlink -f "${KERNEL_DIR}/../KERNEL_OBJ")}
KERNEL_ARCH=arm64
KERNEL_DEFCONFIG=${KERNEL_DEFCONFIG:-frieza_defconfig}
KERNEL_CROSS_COMPILE=${KERNEL_CROSS_COMPILE:-$(readlink -f "${KERNEL_DIR}/../cit-aarch64-linux-android-4.9")/bin/aarch64-linux-android-}

mkdir -p "${KERNEL_OUT}"
make -C "${KERNEL_DIR}" -j $(nproc) O="${KERNEL_OUT}" ARCH=${KERNEL_ARCH} CROSS_COMPILE="${KERNEL_CROSS_COMPILE}" ${KERNEL_DEFCONFIG} $@ \
  && make -C "${KERNEL_DIR}" -j $(nproc) O="${KERNEL_OUT}" ARCH=${KERNEL_ARCH} CROSS_COMPILE="${KERNEL_CROSS_COMPILE}" $@
