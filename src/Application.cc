#include "Application.h"
#include "NodeConfiguration.h"

using namespace reflex;

Application::Application(Pool& pool) :
      actTimeout(*this)
    , actReceivedData(*this)
    , timer(VirtualTimer::PERIODIC)
    , pool(pool)
    , counter(0)
    , state(START)
    , sender(false)

{

    led.turnOnColor(LED::red,true);
    if(sender == true){

        // setup timer
        timer.set(1000);
        //connect event with activity
        event.init(&actTimeout);
        //connect timer with event
        timer.connect_output(&event);
    }else{
        dataFromRadio.init(&actReceivedData);
    }



}

void Application::receivedData(){
    Buffer *buf = (Buffer*)dataFromRadio.get();
    uint8 number;
    buf->read(number);
//    led.toggleAll();
    led.displayNumber(number);


}


void Application::timeout()
{

    switch(++counter) {

    case (START - 5):
        counter = MID;
        break;


    case (MID - 5):
        counter = END;
        break;


    case (END - 5):
        counter = START;
        break;


    default:
        // do nothing
        break;
    }


    led.toggleAll();
    // invoke internal memory management
    Buffer *buf = new(&getApplication().pool) Buffer(&getApplication().pool);
    if(0 != buf) {
        buf->write(counter);
        out_sendToRadio->assign(buf);
    }
}

