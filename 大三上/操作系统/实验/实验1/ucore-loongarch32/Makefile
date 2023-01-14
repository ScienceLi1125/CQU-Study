# LAB CONFIG BEGIN

# Warning: If you changed anything in Makefile, 
# you should execute `make clean` first.

LAB1	:= -DLAB1_EX2 -DLAB1_EX3 -D_SHOW_100_TICKS -D_SHOW_SERIAL_INPUT
# LAB2	:= -DLAB2_EX1 -DLAB2_EX2 -DLAB2_EX3
# LAB3	:= -DLAB3_EX1 -DLAB3_EX2
# LAB4	:= -DLAB4_EX1 -DLAB4_EX2

# LAB CONFIG END

ifdef LAB4
	USER_OBJ_MODE	:= initrd
else
	USER_OBJ_MODE	:= piggy
endif

EMPTY	:=
SPACE	:= $(EMPTY) $(EMPTY)
SLASH	:= /

V       := @

GCCPREFIX:= loongarch32r-linux-gnusf-

QEMU:= qemu-system-loongarch32
QEMUOPTS:= -M ls3a5k32 -m 32 -nographic

# use the same qemu as use_for_linux

TERMINAL := gnome-terminal
TERMINALOPT := -e

# eliminate default suffix rules
.SUFFIXES: .c .S .h

# define compiler and flags

HOSTCC		:= gcc
HOSTCFLAGS	:= -g -Wall -O2

GDB		:= loongarch32r-linux-gnusf-gdb

CC :=$(GCCPREFIX)gcc
LAB_FLA	:= $(LAB1) $(LAB2) $(LAB3) $(LAB4)
CFLAGS	:= $(LAB_FLA) -fno-builtin-fprintf -fno-builtin -nostdlib  -nostdinc -g -G0 -Wa,-O0 -fno-pic -msoft-float -ggdb -gstabs 
CTYPE	:= c S

LD      := $(GCCPREFIX)ld
AR      := $(GCCPREFIX)ar
LDFLAGS	+= -nostdlib -m elf32loongarch

OBJCOPY := $(GCCPREFIX)objcopy
OBJDUMP := $(GCCPREFIX)objdump

COPY	:= cp
MKDIR   := mkdir -p
MV		:= mv
RM		:= rm -f
AWK		:= awk
SED		:= sed
SH		:= sh
TR		:= tr
TOUCH	:= touch -c

TAR		:= tar
ZIP		:= gzip

OBJDIR	:= obj
BINDIR	:= bin
SRCDIR  := kern
DEPDIR  := dep

MODULES   := init driver libs trap mm debug sync process schedule syscall fs fs/vfs fs/sfs fs/devs

SRC_DIR   := $(addprefix $(SRCDIR)/,$(MODULES))
BUILD_DIR := $(addprefix $(OBJDIR)/,$(MODULES))
DEP_DIR   := $(addprefix $(DEPDIR)/,$(MODULES))
VPATH     += $(SRC_DIR)

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ       := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
ASMSRC    := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.S))
OBJ       += $(patsubst $(SRCDIR)/%.S, $(OBJDIR)/%.o, $(ASMSRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))
INCLUDES  += -I$(SRCDIR)/include

override ON_FPGA ?= n

ifeq ($(ON_FPGA), y)
	USER_APPLIST:= sh ls cat
	INITRD_BLOCK_CNT:=700 
else
	USER_APPLIST:= pwd cat sh ls forktest yield hello faultreadkernel faultread badarg waitkill pgdir exit sleep echo spin forktree
	INITRD_BLOCK_CNT:=4000
endif

USER_SRCDIR := user
USER_OBJDIR := $(OBJDIR)/$(USER_SRCDIR)
USER_LIB_OBJDIR := $(USER_OBJDIR)/libs
USER_INCLUDE := -I$(USER_SRCDIR)/libs

USER_APP_BINS:= $(addprefix $(USER_OBJDIR)/, $(USER_APPLIST))

USER_LIB_SRCDIR := $(USER_SRCDIR)/libs
USER_LIB_SRC := $(foreach sdir,$(USER_LIB_SRCDIR),$(wildcard $(sdir)/*.c))
USER_LIB_OBJ := $(patsubst $(USER_LIB_SRCDIR)/%.c, $(USER_LIB_OBJDIR)/%.o, $(USER_LIB_SRC))
USER_LIB_OBJ += $(USER_LIB_OBJDIR)/initcode.o
USER_LIB    := $(USER_OBJDIR)/libuser.a

BUILD_DIR   += $(USER_LIB_OBJDIR)
BUILD_DIR   += $(USER_OBJDIR)


DEPENDS := $(patsubst $(SRCDIR)/%.c, $(DEPDIR)/%.d, $(SRC))

MAKEDEPEND = $(CLANG) -M $(CFLAGS) $(INCLUDES) -o $(DEPDIR)/$*.d $<
#vpath %.c $(SRC_DIR)
#vpath %.S $(SRC_DIR)

.PHONY: all checkdirs clean qemu debug

all: checkdirs $(OBJDIR)/ucore-kernel-$(USER_OBJ_MODE)

$(shell mkdir -p $(DEP_DIR))

$(OBJDIR)/ucore-kernel:  checkdirs $(OBJ) tools/kernel.ld
	$(V)$(LD) -nostdlib -n -G 0 -static -T tools/kernel.ld $(OBJ) -o $@

$(OBJDIR)/ucore-kernel-piggy: $(BUILD_DIR)  $(OBJ) $(USER_APP_BINS) tools/kernel.ld
	$(V)$(LD) -nostdlib -n -G 0 -static -T tools/kernel.ld $(OBJ) \
					$(addsuffix .piggy.o, $(USER_APP_BINS)) -o $@
	$(V)$(OBJDUMP) -S $@ > $(OBJDIR)/kernel.asm
	$(V)$(OBJDUMP) -t $@ | $(SED) '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(OBJDIR)/kernel.sym

$(DEPDIR)/%.d: $(SRCDIR)/%.c
	@echo DEP $<
	$(V)set -e; rm -f $@; \
		$(CC) -MM -MT "$(OBJDIR)/$*.o $@" $(CFLAGS) $(INCLUDES) $< > $@; 

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(V)$(CC) -c $(INCLUDES) $(CFLAGS) $(MACH_DEF) $<  -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	$(V)$(CC) -c -fno-pic -D__ASSEMBLY__ $(MACH_DEF) $(INCLUDES) -g -G0  $<  -o $@

checkdirs: $(BUILD_DIR) $(DEP_DIR)

$(BUILD_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

clean:
	-rm -rf $(DEPDIR)
	-rm -rf boot/loader.o boot/loader boot/loader.bin
	-rm -rf $(OBJDIR)

qemu: $(OBJDIR)/ucore-kernel-$(USER_OBJ_MODE)
	$(V)$(QEMU) $(QEMUOPTS) -kernel $(OBJDIR)/ucore-kernel-$(USER_OBJ_MODE)

debug: $(OBJDIR)/ucore-kernel-$(USER_OBJ_MODE)
	$(V)$(QEMU) $(QEMUOPTS) -kernel $(OBJDIR)/ucore-kernel-$(USER_OBJ_MODE) -S -s

gdb: $(OBJDIR)/ucore-kernel-$(USER_OBJ_MODE)
	$(V)$(GDB) $(OBJDIR)/ucore-kernel-$(USER_OBJ_MODE)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

#user lib

$(USER_LIB): $(BUILD_DIR) $(USER_LIB_OBJ)
	$(V)$(AR) rcs $@ $(USER_LIB_OBJ)

#user applications
define make-user-app
$1: $(BUILD_DIR) $(addsuffix .o,$1) $(USER_LIB)
	$(V)$(LD) -T $(USER_LIB_SRCDIR)/user.ld  $(addsuffix .o,$1) --whole-archive $(USER_LIB) -o $$@
	$(V)$(SED) 's/$$$$FILE/$(notdir $1)/g' tools/piggy.S.in > $1.S
	$(V)$(CC) -c $1.S -o $$@.piggy.o
endef

$(foreach bdir,$(USER_APP_BINS),$(eval $(call make-user-app,$(bdir))))

$(USER_OBJDIR)/%.o: $(USER_SRCDIR)/%.c
	$(V)$(CC) -c  $(USER_INCLUDE) -I$(SRCDIR)/include $(CFLAGS)  $<  -o $@

$(USER_OBJDIR)/%.o: $(USER_SRCDIR)/%.S
	$(V)$(CC) -c -fno-pic -D__ASSEMBLY__ $(USER_INCLUDE) -I$(SRCDIR)/include -g -G0  $<  -o $@


# filesystem
TOOL_MKSFS := tools/mksfs
ROOTFS_DIR:= $(OBJDIR)/rootfs
ROOTFS_IMG:= $(OBJDIR)/initrd.img
$(TOOL_MKSFS): tools/mksfs.c
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

$(OBJDIR)/initrd.img.o: $(TOOL_MKSFS) $(USER_APP_BINS)
	$(V)rm -rf $(ROOTFS_DIR) $(ROOTFS_IMG)
	$(V)mkdir $(ROOTFS_DIR)
	$(V)cp $(USER_APP_BINS) $(ROOTFS_DIR)
	$(V)cp -r $(USER_SRCDIR)/_archive/* $(ROOTFS_DIR)/
	$(V)dd if=/dev/zero of=$(ROOTFS_IMG) count=$(INITRD_BLOCK_CNT)
	$(V)$(TOOL_MKSFS) $(ROOTFS_IMG) $(ROOTFS_DIR)
	$(V)$(SED) 's%_FILE_%$(ROOTFS_IMG)%g' tools/initrd_piggy.S.in > $(USER_OBJDIR)/initrd_piggy.S
	$(V)$(CC) -c $(USER_OBJDIR)/initrd_piggy.S -o $(OBJDIR)/initrd.img.o

$(OBJDIR)/ucore-kernel-initrd: $(BUILD_DIR) $(OBJ) tools/kernel.ld $(OBJDIR)/initrd.img.o
	$(V)$(LD) -nostdlib -n -G 0 -static -T tools/kernel.ld $(OBJ) \
				 $(OBJDIR)/initrd.img.o -o $@
	$(V)$(OBJDUMP) -S $@ > $(OBJDIR)/kernel.asm
	$(V)$(OBJDUMP) -t $@ | $(SED) '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $(OBJDIR)/kernel.sym
	
