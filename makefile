# ----------------------------
# Set NAME to the program name
# Set ICON to the png icon file name
# Set DESCRIPTION to display within a compatible shell
# Set COMPRESSED to "YES" to create a compressed program
# ----------------------------

NAME        ?= SURVIVCE
COMPRESSED  ?= NO
ICON        ?= icon.png
DESCRIPTION ?= "SurvivalCE - CC24 Entry"

# ----------------------------

include $(CEDEV)/include/.makefile
