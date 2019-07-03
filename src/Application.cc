#include "Application.h"
#include "NodeConfiguration.h"

using namespace reflex;

Application::Application(Pool& pool) :
      actTimeout(*this)
    , actReceivedData(*this)
    , actTurnOff(led)
    , timer(VirtualTimer::ONESHOT)
    , turnOffTimer(VirtualTimer::ONESHOT)
    , pool(pool)
    , counter(0)

{

    led.turnOnColor(LED::red, true);

//        led.turnOnLED(1, true);
        // setup timer
        timer.set(2000);
        //connect event with activity
        event.init(&actTimeout);
        //connect timer with event
        timer.connect_output(&event);

        turnOffEvent.init(&actTurnOff);
        turnOffTimer.connect_output(&turnOffEvent);

        dataFromRadio.init(&actReceivedData);



}

void Application::receivedData(){
    Buffer *buf = (Buffer*)dataFromRadio.get();
    buf->read(counter);
    buf->downRef();
    led.displayNumber(counter);

    timer.set(2000);
    turnOffTimer.set(500);

}

void Application::timeout()
{

    counter++;

    if(counter <= 0){
        counter = 1;
    }
    if(counter > 10){
        counter = 1;
    }


    led.displayNumber(counter);
    // invoke internal memory management
    Buffer *buf = new(&getApplication().pool) Buffer(&getApplication().pool);
    if(0 != buf) {
        buf->write(counter);
        out_sendToRadio->assign(buf);
    }
}

