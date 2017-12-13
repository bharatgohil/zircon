# zx_interrupt_wait

## NAME

interrupt_wait - wait for an interrupt on an interrupt handle

## SYNOPSIS

```
#include <zircon/syscalls.h>

zx_status_t zx_interrupt_wait(zx_handle_t handle, uint64_t* out_slots);
```

## DESCRIPTION

**interrupt_wait**() is a blocking syscall which causes the caller to
wait until either an interrupt occurs for the interrupt vector associated
with *handle* or another thread calls **zx_interrupt_signal()** or 
**zx_interrupt_cancel()** on *handle*.

Upon successful return, the *out_slots* parameter returns a bitmask
of the slots that have been signalled, either via a hardware interrupt
or another thread calling **zx_interrupt_signal()** to signal a virtual interrupt.

For level triggered hardware interrupts, **interrupt_wait()** will mask the interrupt
before returning and unmask the interrupt when it is called again the next time.
For edge triggered interrupts, the interrupt remains unmasked.

## RETURN VALUE

**interrupt_wait**() returns **ZX_OK** when an interrupt has been received,
or **ZX_ERR_CANCELED** if **zx_interrupt_cancel()** was called by another
thread on *handle*.

## ERRORS

**ZX_ERR_CANCELED**  *handle* was signalled via **zx_interrupt_signal()**.
**ZX_ERR_BAD_HANDLE**  *handle* is not a valid handle.

## SEE ALSO

[interrupt_create](interrupt_create.md),
[interrupt_bind](interrupt_bind.md),
[interrupt_unbind](interrupt_unbind.md),
[interrupt_get_timestamp](interrupt_get_timestamp.md),
[interrupt_signal](interrupt_signal.md),
[interrupt_cancel](interrupt_cancel.md).
[handle_close](handle_close.md).
