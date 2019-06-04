/*
 * Application.h
 *
 *  Created on: 01.04.2018
 *      Author: Hannes Menzel
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "conf.h"
#include "reflex/types.h"
#include "reflex/memory/Buffer.h"
#include "reflex/memory/Pool.h"
#include "reflex/sinks/SingleValue.h"
#include "reflex/sinks/Event.h"
#include "reflex/sinks/Queue.h"
#include "reflex/scheduling/ActivityFunctor.h"
#include "reflex/timer/VirtualTimer.h"
#include "LED.h"


namespace reflex {

class Application {

public:

	Application(Pool& pool);

private:

	/**
	 * handler for timeout
	 */
	void timeoutRed();
	void timeoutGreen();
	void timeoutBlue();


	/**
	 * activity functor for timeout
	 */
	ActivityFunctor<Application, &Application::timeoutRed> actTimeoutRed;
	ActivityFunctor<Application, &Application::timeoutGreen> actTimeoutGreen;
	ActivityFunctor<Application, &Application::timeoutBlue> actTimeoutBlue;


	/**
	 * timer for time events
	 */
	reflex::VirtualTimer timerRed;
	reflex::VirtualTimer timerBlue;
	reflex::VirtualTimer timerGreen;

	/**
	 * event that is notified by timer
	 */
	reflex::Event eventRed;
	reflex::Event eventGreen;
	reflex::Event eventBlue;

	// our memory management
	Pool& pool;
	LED led;

};
}

#endif /* APPLICATION_H_ */
