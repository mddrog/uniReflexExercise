#/*
# *	REFLEX - Real-time Event FLow EXecutive
# *
# *	A lightweight operating system for deeply embedded systems.
# *
# *	Revision:	 $Id: Sources.mk 1168 2009-08-04 16:28:41Z menzha1 $
# *	Author:		 Hannes Menzel
# */

CC_SOURCES_CONTROLLER += \
	usci/RadioSPI.cc \
	crc16/Crc16.cc \
	wdt/WDT_A.cc
	
CC_SOURCES_LIB += \
	utils/NodeUtils.cc \
	utils/NodeInfoBase.cc

CC_SOURCES_PLATFORM += \
	rf/RADIO.cc \
	rf/CC1101.cc

