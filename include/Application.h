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

    /**
     *
     */
    inline void connect_out_sendDataToRadio(reflex::Queue<reflex::Buffer*>* sink)
    {
        out_sendToRadio = sink;
    }

    /**
     * @return the input for data which has to be sent
     */
    inline Queue<Buffer*>* get_dataFromRadio()
    {
        return &dataFromRadio;
    }

private:


    Queue<Buffer*> dataFromRadio;
//
    void receivedData();
    /**
     * handler for timeout
     */
    void timeout();


    /**
     * activity functor for timeout
     */
    ActivityFunctor<Application, &Application::timeout> actTimeout;
    ActivityFunctor<LED, &LED::turnOffAll> actTurnOff;


    ActivityFunctor<Application, &Application::receivedData> actReceivedData;



    /**
     * timer for time events
     */
    reflex::VirtualTimer timer;
    reflex::VirtualTimer turnOffTimer;


    /**
     * event that is notified by timer
     */
    reflex::Event event;
    reflex::Event turnOffEvent;



    // our memory management
    Pool& pool;


    //pointer to a sink -> if data are copied into the buffer, then RADIO::transmit is notified
    reflex::Queue<reflex::Buffer*> *out_sendToRadio;



    // indicator for red
    uint8 counter;


    LED led;

    void sendData(uint8 number);
};
}

#endif /* APPLICATION_H_ */
