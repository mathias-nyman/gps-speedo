SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

SRC += $(call target_files,,*.c)
CPPSRC += $(call target_files,,*.cpp)

INCLUDE_DIRS += $(SELF_DIR)
INCLUDE_DIRS += $(SELF_DIR)/libs/gfx
INCLUDE_DIRS += $(SELF_DIR)/libs/sharp-memory-display
INCLUDE_DIRS += $(SELF_DIR)/libs/tiny-gps

CPPFLAGS += -DARDUINO=100
#TODO: fix compiler warnings of Adafruit_GFX
#CPPFLAGS += - -Werror
