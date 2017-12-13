// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <unittest/unittest.h>
#include <zircon/syscalls.h>

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>

#define BOUND_SLOT 0
#define UNBOUND_SLOT 1

extern zx_handle_t get_root_resource(void);

// Tests support for virtual interrupts
static bool interrupt_test(void) {
    BEGIN_TEST;

    zx_handle_t handle;
    zx_handle_t rsrc = get_root_resource();
    uint64_t slots;
    zx_time_t timestamp;
    zx_time_t signaled_timestamp = 12345;

    ASSERT_EQ(zx_interrupt_create(rsrc, 0, &handle), ZX_OK, "");
    ASSERT_EQ(zx_interrupt_bind(handle, ZX_INTERRUPT_MAX_WAIT_SLOTS, rsrc, 0, ZX_INTERRUPT_VIRTUAL),
              ZX_ERR_INVALID_ARGS, "");
    ASSERT_EQ(zx_interrupt_bind(handle, BOUND_SLOT, rsrc, 0, ZX_INTERRUPT_VIRTUAL), ZX_OK, "");
    ASSERT_EQ(zx_interrupt_bind(handle, BOUND_SLOT, rsrc, 0, ZX_INTERRUPT_VIRTUAL),
                                ZX_ERR_ALREADY_BOUND, "");

    ASSERT_EQ(zx_interrupt_get_timestamp(handle, BOUND_SLOT, &timestamp), ZX_ERR_BAD_STATE, "");

    ASSERT_EQ(zx_interrupt_signal(handle, UNBOUND_SLOT, signaled_timestamp),
                                  ZX_ERR_INVALID_ARGS, "");
    ASSERT_EQ(zx_interrupt_signal(handle, BOUND_SLOT, signaled_timestamp), ZX_OK, "");

    ASSERT_EQ(zx_interrupt_wait(handle, &slots), ZX_OK, "");
    ASSERT_EQ(slots, (1u << BOUND_SLOT), "");

    ASSERT_EQ(zx_interrupt_get_timestamp(handle, UNBOUND_SLOT, &timestamp), ZX_ERR_NOT_FOUND, "");
    ASSERT_EQ(zx_interrupt_get_timestamp(handle, BOUND_SLOT, &timestamp), ZX_OK, "");
    ASSERT_EQ(timestamp, signaled_timestamp, "");

    ASSERT_EQ(zx_interrupt_cancel(handle), ZX_OK, "");
    ASSERT_EQ(zx_interrupt_wait(handle, &slots), ZX_ERR_CANCELED, "");

    ASSERT_EQ(zx_interrupt_unbind(handle, UNBOUND_SLOT), ZX_ERR_NOT_FOUND, "");
    ASSERT_EQ(zx_interrupt_unbind(handle, BOUND_SLOT), ZX_OK, "");
    ASSERT_EQ(zx_interrupt_unbind(handle, BOUND_SLOT), ZX_ERR_NOT_FOUND, "");

    ASSERT_EQ(zx_handle_close(handle), ZX_OK, "");

    END_TEST;
}

BEGIN_TEST_CASE(interrupt_tests)
RUN_TEST(interrupt_test)
END_TEST_CASE(interrupt_tests)
