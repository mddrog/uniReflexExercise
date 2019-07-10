#/*
# *	REFLEX - Real-time Event FLow EXecutive
# *
# *	A lightweight operating system for deeply embedded systems.
# *
# *	Author:		 Karsten Walther
# */

CC_SOURCES_APPLICATION += \
	src/Application.cc \
	src/main.cc \
	src/LED.cc \
	src/Random.cc

CC_SOURCES_LIB += \
	memory/FreeList.cc \
	memory/Pool.cc \
	memory/Buffer.cc \
	memory/PoolManager.cc

CC_SOURCES_CONTROLLER += \


sinclude $(APPLICATIONPATH)/platform/$(PLATFORM)/Sources.mk
sinclude $(APPLICATIONPATH)/lib/sens4u/Sources.mk
