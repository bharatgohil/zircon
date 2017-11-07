// Copyright 2017 The Fuchsia Authors
//
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT

#pragma once

#include <zircon/syscalls/resource.h>
#include <zircon/types.h>

// Resource constants (ZX_RSRC_KIND_..., etc) are located
// in system/public/zircon/syscalls/resource.h

// Determines if this handle is to a resource of the specified
// kind *or* to the root resource, which can stand in for any kind.
// Used to provide access to privileged syscalls.
zx_status_t validate_resource(zx_handle_t handle, uint32_t kind);

// Validates a resource based on type and low/high range;
zx_status_t validate_ranged_resource(zx_handle_t handle, uint32_t kind,
                                     uint64_t low, uint64_t high);

// Validates mapping an MMIO range based on a resource handle
static inline zx_status_t validate_resource_mmio(
    zx_handle_t handle, uintptr_t base, size_t length) {

    if (length < 1 || UINT64_MAX - base < length) {
        return ZX_ERR_INVALID_ARGS;
    }
    return validate_ranged_resource(handle, ZX_RSRC_KIND_MMIO,
                                    base, base + length - 1);
}

// Validates creation of an interrupt object based on a resource handle
static inline zx_status_t validate_resource_irq(zx_handle_t handle,
                                                uint32_t irq) {
    return validate_ranged_resource(handle, ZX_RSRC_KIND_IRQ, irq, irq);
}

// Validates mapping a device IO range based on a resource handle
static inline zx_status_t validate_resource_device_io(
    zx_handle_t handle, uint32_t io_addr, uint32_t length) {
    uint64_t base = io_addr;
    if (length < 1 || UINT64_MAX - base < length) {
        return ZX_ERR_INVALID_ARGS;
    }
    return validate_ranged_resource(handle, ZX_RSRC_KIND_DEVICE_IO,
                                    base, base + length - 1);
}
