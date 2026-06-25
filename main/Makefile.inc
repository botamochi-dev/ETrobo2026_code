mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
    debug_log.o

APPL_LIBS += -lm

APPL_DIRS += 

INCLUDES += \
