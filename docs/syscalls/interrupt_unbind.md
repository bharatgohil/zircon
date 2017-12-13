# interrupt_unbind

## NAME

interrupt_unbind - Unind an interrupt vector from interrupt handle

## SYNOPSIS

```
#include <zircon/syscalls.h>

zx_status_t zx_interrupt_unbind(zx_handle_t handle, uint32_t slot);

```

## DESCRIPTION




## SEE ALSO

[interrupt_create](interrupt_create.md),
[interrupt_bind](interrupt_bind.md),
[interrupt_wait](interrupt_wait.md),
[interrupt_get_timestamp](interrupt_get_timestamp.md),
[interrupt_signal](interrupt_signal.md),
[interrupt_cancel](interrupt_cancel.md).
[handle_close](handle_close.md).
