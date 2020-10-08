# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= SURVIVCE
COMPRESSED  ?= NO
ICON        ?= pixil-frame-0 (1).png
DESCRIPTION ?= "SurvivalCE - CC24 Entry by Michael0x18 and TimmyTurner62"

# ----------------------------

include $(CEDEV)/include/.makefile
