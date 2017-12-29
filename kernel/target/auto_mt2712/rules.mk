# Copyright 2017 The Fuchsia Authors
#
# Use of this source code is governed by a MIT-style
# license that can be found in the LICENSE file or at
# https://opensource.org/licenses/MIT

LOCAL_DIR := $(GET_LOCAL_DIR)

PLATFORM := generic-arm

DEVICE_TREE := $(GET_LOCAL_DIR)/device-tree.dtb

KERNEL_LOAD_OFFSET := 0x00080000

include make/kernel-images.mk

# build MDI
MDI_SRCS := $(LOCAL_DIR)/auto_mt2712.mdi

