$(info TX_EXAMPLE is $(TX_EXAMPLE))
$(info RX_EXAMPLE is $(RX_EXAMPLE))
$(info LOOPBACK_EXAMPLE is $(LOOPBACK_EXAMPLE))

ifeq (y,$(strip $(TX_EXAMPLE)))
$(info Adding TX_EXAMPLE)
CFLAGS += -DTX_EXAMPLE
SRCS += $(PROJECT)/src/examples/tx/uart_tx.c
INCS += $(PROJECT)/src/examples/tx/uart_tx.h
else ifeq (y,$(strip $(RX_EXAMPLE)))
$(info Adding RX_EXAMPLE)
CFLAGS += -DRX_EXAMPLE
SRCS += $(PROJECT)/src/examples/rx/uart_rx.c
INCS += $(PROJECT)/src/examples/rx/uart_rx.h
else ifeq (y,$(strip $(LOOPBACK_EXAMPLE)))
$(info Adding LOOPBACK_EXAMPLE)
CFLAGS += -DLOOPBACK_EXAMPLE
SRCS += $(PROJECT)/src/examples/loopback/uart_loopback.c
INCS += $(PROJECT)/src/examples/loopback/uart_loopback.h
endif
