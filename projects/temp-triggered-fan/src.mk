include $(PROJECT)/src/platform/$(PLATFORM)/platform_src.mk
SRCS += $(PROJECT)/src/platform/$(PLATFORM)/gpio_trigger_read.c

INCS += $(PROJECT)/src/common/common_data.h

INCS += $(PROJECT)/src/platform/platform_includes.h

INCS += $(PROJECT)/src/platform/$(PLATFORM)/parameters.h

INCS += $(INCLUDE)/no_os_delay.h     \
		$(INCLUDE)/no_os_error.h     \
		$(INCLUDE)/no_os_gpio.h      \
		$(INCLUDE)/no_os_timer.h      \
		$(INCLUDE)/no_os_alloc.h \
		$(INCLUDE)/no_os_print_log.h \
        	$(INCLUDE)/no_os_mutex.h

SRCS += $(DRIVERS)/api/no_os_gpio.c \
		$(DRIVERS)/api/no_os_timer.c  \
		$(NO-OS)/util/no_os_alloc.c \
		$(NO-OS)/util/no_os_mutex.c

