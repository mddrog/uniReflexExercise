#ifndef NodeConfiguration_h
#define NodeConfiguration_h
/*
 *	REFLEX - Real-time Event FLow EXecutive
 *
 *	A lightweight operating system for deeply embedded systems.
 *
 *
 *	Class(ses):	 Application
 *
 *	Author:		 Karsten Walther
 *
 *	Description: Implements the System
 *
 *
 *    This file is part of REFLEX.
 *
 *    Copyright 2010 BTU Cottbus, Department for Distributed Systems and 
 *    Operating Systems. All rights reserved.
 *    
 *    Redistribution and use in source and binary forms, with or without 
 *    modification, are permitted provided that the following conditions
 *    are met:
 *    
 *       1. Redistributions of source code must retain the above copyright 
 *          notice, this list of conditions and the following disclaimer.
 * 
 *       2. Redistributions in binary form must reproduce the above copyright
 *          notice, this list of conditions and the following disclaimer in
 *          the documentation and/or other materials provided with the 
 *          distribution.
 * 
 *    THIS SOFTWARE IS PROVIDED BY BTU COTTBUS, DEPARTMENT FOR DISTRIBUTED 
 *    SYSTEMS AND OPERATING SYSTEMS ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 *    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 *    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 *    NO EVENT SHALL BTU COTTBUS, DEPARTMENT FOR DISTRIBUTED SYSTEMS AND 
 *    OPERATING SYSTEMS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *    The views and conclusions contained in the software and documentation 
 *    are those of the authors a	Buffer* sendBuf = new ((FreeList*) &pool) Buffer(&pool);

	char hello[5];
	hello[0] = 'h';
	hello[1] = 'e'

	sendBuf->write(hello, 5);

	dataToUART->assign(sendBuf);nd should not be interpreted as representing
 *    official policies, either expressed or implied, of BTU Cottbus, 
 *    Department for Distributed Systems and Operating Systems.
 *
 * */

#include "Application.h"
#include "reflex/types.h"


#include "reflex/memory/PoolManager.h"
#include "reflex/memory/SizedPool.h"

#include "reflex/System.h"

#include "reflex/data_types.h"

#include "reflex/io/Ports.h"

#include "reflex/data_types.h"

#include "reflex/timer/VirtualTimer.h"
#include "reflex/sinks/Event.h"
#include "reflex/sinks/SingleValue.h"

#include "reflex/scheduling/ActivityFunctor.h"


#include "reflex/wdt/WDT_A.h"
#include "reflex/driverConfiguration/WDT_AConfiguration.h"

#include "reflex/rf/RADIO.h"


// SOLUTION


namespace reflex {

/**Define different powergroups for an application. To use the available groups provided by the powermanager are highly 
 * recommended.
 */
enum PowerGroups {
	RADIO = reflex::PowerManager::GROUP2,
	DEFAULT = reflex::PowerManager::GROUP1,
	DISABLED = reflex::PowerManager::NOTHING
};

class NodeConfiguration 
	: public System
{

public:

	NodeConfiguration() 
		: System()
		, pool(0) //the Buffer is only used as FiFo. So stacksize is 0 @see Buffer
		, radio(pool)
		, application(pool)
	{

		// connect output of output channel

		WDT_AConfiguration cfgWDT;
		cfgWDT.setClockSource(mcu::wdt_a::ACLK); // 32kHz
		cfgWDT.setIntervall(mcu::wdt_a::Ivl512k);
		cfgWDT.setTimerMode(true);
		cfgWDT.start();
		cfgWDT.performConfiguration(watchdog.get_in_confData());

		timer.setGroups(DEFAULT); // put system timer in default group
		radio.setGroups(DEFAULT);

		//setting up the radio configuration
		RadioConfiguration cfg;
		cfg.setCCA(true);
		cfg.setLogicalChannel(3);
		cfg.setSendingTOS(false);
		cfg.setSignalAttenuation(0);
		cfg.setWhitening(false);
		cfg.setTransmissionTime(150);
		cfg.setContinuousTransmission(false);
		cfg.setAccessPointMode(false);
		cfg.performConfiguration(radio.get_in_confData());
        powerManager.enableGroup(DEFAULT); // this enables all registered entities in DEFAULT group (starts system timer)

	    	//if data are ready to send, then the radio must notified
		application.connect_out_sendDataToRadio(radio.get_in_input());
		radio.connect_out_data(application.get_dataFromRadio());
		
	}


	PoolManager poolManager;
	SizedPool<IOBufferSize,NrOfStdOutBuffers> pool; ///< a pool of bufferobject with static size

	// low-level driver for radio communcation 868MHz
	FeuerWhere::RADIO radio;

	Application application;

	/**
	 * watchdog to force a reset after a certain time
	 */
	mcu::WDT_A watchdog;
	

};


inline NodeConfiguration& getApplication()
{
	extern NodeConfiguration system;
	return system;
}




} //reflex



#endif
