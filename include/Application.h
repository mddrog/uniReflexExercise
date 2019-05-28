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


namespace reflex {

class Application {

public:

	Application(Pool& pool);

private:

	/**
	 * handler for timeout
	 */
	void timeout();


	/**
	 * activity functor for timeout
	 */
	ActivityFunctor<Application, &Application::timeout> actTimeout;


	/**
	 * timer for time events
	 */
	reflex::VirtualTimer timer;

	/**
	 * event that is notified by timer
	 */
	reflex::Event event;

	// our memory management
	Pool& pool;

};
}

#endif /* APPLICATION_H_ */
