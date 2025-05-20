ifeq (y,$(strip $(TX_EXAMPLE)))
CFLAGS += -DTX_EXAMPLE
SRCS += $(PROJECT)/src/examples/tx/uart_tx.c
INCS += $(PROJECT)/src/examples/tx/uart_tx.h
endif

ifeq (y,$(strip $(RX_EXAMPLE)))
CFLAGS += -DRX_EXAMPLE
SRCS += $(PROJECT)/src/examples/rx/uart_rx.c
INCS += $(PROJECT)/src/examples/rx/uart_rx.h
endif

