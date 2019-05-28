#/*
# *	REFLEX - Real-time Event FLow EXecutive
# *
# *	A lightweight operating system for deeply embedded systems.
# *
# *	Revision:	 $Id: Makefile_default 1213 2009-09-29 12:57:47Z asieber $
# *	Author:		 Karsten Walther
# */
##########################################################################
# Common variables that must be defined by user
##########################################################################


# The name of the game
APPLICATION = LEDSetup
# target platform
PLATFORM = FeuerWhere
# compile in debug mode ?
DEBUG = 1
# accessPoint has nodeid 0
NODEID = 77
# define here whether your code should support wireless update
# uncomment if not -> for this application WIRELESS_UPDATE flag has to be active
WIRELESS_UPDATE = 1

# specifies number of nodes supported by network layer
SUPPORTED_NODES = 64

OBJDIR = .

# choosing scheduling scheme
SCHEDSCHEME = FIFO_SCHEDULING

APPLICATIONPATH = ../../..
REFLEXPATH = $(APPLICATIONPATH)/../..

INCLUDES += -I$(APPLICATIONPATH)/include \
	-I$(APPLICATIONPATH)/platform/$(PLATFORM)/include

	
ifdef NODEID
DEFINED_REFLEX_VARS += "Nodeid = " $(NODEID)"\\n"
CXXFLAGS += -DNODEID=$(NODEID)
else
MISSING_REFLEX_VARS += "NODEID - a NODEID is needed to built this application\\n"
endif

ifdef WIRELESS_UPDATE
DEFINED_REFLEX_VARS += "wireless update is active\\n"
CXXFLAGS += -DWIRELESS_UPDATE=1
else
MISSING_REFLEX_VARS += "wireless update is not active\\n"
endif

ifdef SUPPORTED_NODES
DEFINED_REFLEX_VARS += $(SUPPORTED_NODES) " nodes are supported by network protocol\\n"
CXXFLAGS += -DSUPPORTED_NODES=$(SUPPORTED_NODES)
else
MISSING_REFLEX_VARS += " number of supported nodes were not determined\\n"
endif

##########################################################################
# Platform specific variables that must be defined by user:
##########################################################################
BSL = $(REFLEXPATH)/platform/TMOTESKY/tools/pybsl/bsl.py
BUILDPLATFORM = $(shell uname -s)
ifeq ($(BUILDPLATFORM), Darwin)
     	TTYUSB = $(shell ls /dev/tty.usbserial* | sort | head -n1)
	# USB = /dev/tty.usbserial-M4AH6DF2
	USB = $(TTYUSB)
else
	USB = /dev/ttyUSB1
endif

##########################################################################
# Include the main Makefile
##########################################################################
include $(REFLEXPATH)/system/StandardMake.mk
