$(info TX_EXAMPLE is $(TX_EXAMPLE))
$(info RX_EXAMPLE is $(RX_EXAMPLE))
$(info LOOPBACK_EXAMPLE is $(LOOPBACK_EXAMPLE))
$(info BMS_DEBUG is $(BMS_DEBUG))

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
else ifeq (y,$(strip $(BMS_DEBUG)))
$(info Adding BMS_DEBUG)
CFLAGS += -DBMS_DEBUG
SRCS += $(PROJECT)/src/examples/bms_debug/bms_debug.c
INCS += $(PROJECT)/src/examples/bms_debug/bms_debug.h
endif
