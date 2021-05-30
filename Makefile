CC?=gcc
CFLAGS=-Wall -Wextra
LIB=pthread

SDIR := ./src
ADIR := ./app
HDIR := ./headers

SRC := $(wildcard $(SDIR)/*.c)

ASRC := $(SRC) $(wildcard $(ADIR)/*.c)
AOBJ := $(ASRC:%.c=%.o)

OBJ := $(AOBJ)
DEPS := $(OBJ:%.o=%.d)

EXEC := main.out

H_INC := $(foreach d, $(HDIR), -I$d)
L_INC := $(foreach l, $(LIB), -l$l)

ifeq ($(CC),clang)
	C_FLAGS += -Weverything
endif
all: $(EXEC)

$(EXEC): $(AOBJ)
	$(call print_bin,$@)
	$(Q)$(CC) $(C_FLAGS) $(H_INC) $(AOBJ) -o $@ $(L_INC)

%.o:%.c %.d
	$(call print_cc,$<)
	$(Q)$(CC) $(C_FLAGS) $(H_INC) -c $< -o $@

clean:
	$(call print_rm,EXEC)
	$(Q)$(RM) $(EXEC)
	$(Q)$(RM) $(OBJ)
	$(Q)$(RM) $(DEPS)

$(DEPS):

include $(wildcard $(DEPS))