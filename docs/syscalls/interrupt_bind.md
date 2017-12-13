# zx_interrupt_bind

## NAME

interrupt_bind - Bind an interrupt vector to interrupt handle

## SYNOPSIS

```
#include <zircon/syscalls.h>

zx_status_t zx_interrupt_bind(zx_handle_t handle, uint32_t slot, zx_handle_t hrsrc,
                              uint32_t vector, uint32_t options);

```

## DESCRIPTION


## SEE ALSO

[interrupt_create](interrupt_create.md),
[interrupt_unbind](interrupt_unbind.md),
[interrupt_wait](interrupt_wait.md),
[interrupt_get_timestamp](interrupt_get_timestamp.md),
[interrupt_signal](interrupt_signal.md),
[interrupt_cancel](interrupt_cancel.md).
[handle_close](handle_close.md).
