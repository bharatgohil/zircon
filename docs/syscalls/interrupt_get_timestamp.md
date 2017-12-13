# zx_interrupt_get_timestamp

## NAME

interrupt_get_timestamp - Get the timestamp for an interrupt

## SYNOPSIS

```
#include <zircon/syscalls.h>

zx_status_t zx_interrupt_get_timestamp(zx_handle_t handle, uint32_t slot, zx_time_t* out_timestamp);

```

## DESCRIPTION



## SEE ALSO

[interrupt_create](interrupt_create.md),
[interrupt_bind](interrupt_bind.md),
[interrupt_unbind](interrupt_unbind.md),
[interrupt_wait](interrupt_wait.md),
[interrupt_signal](interrupt_signal.md),
[interrupt_cancel](interrupt_cancel.md).
[handle_close](handle_close.md).
