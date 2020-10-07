# ----------------------------
# Program Options
# ----------------------------

NAME         ?= CC24TEST
ICON         ?= icon.png
DESCRIPTION  ?= "CC24 Entry by TimmyTurner62 and Michael0x18"
MAIN_ARGS    ?= NO
COMPRESSED   ?= NO
ARCHIVED     ?= NO

# ----------------------------
# Compile Options
# ----------------------------

OPT_MODE     ?= -Oz
EXTRA_CFLAGS ?= -Wall -Wextra

# ----------------------------
# Debug Options
# ----------------------------

OUTPUT_MAP   ?= NO

include $(CEDEV)/include/.makefile
