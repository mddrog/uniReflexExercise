#include "Application.h"
#include "NodeConfiguration.h"


using namespace reflex;

Application::Application(Pool& pool) :
      actTimeout(*this)
    , actReceivedData(*this)
    , actSend(*this)
    , actStart(*this)
    , actId(*this)
    , actTurnOff(led)
    , timer(VirtualTimer::PERIODIC)
    , startTimer(VirtualTimer::ONESHOT)
    , waitForAnswerTimer(VirtualTimer::ONESHOT)
    , pool(pool)
    , counter(0)
    , randomGenerator(timer.getSystemTime())

{
    led.turnOnColor(LED::red, true);

        timeToWait=randomGenerator.next(50);
        timer.set(1);
        timerEvent.init(&actTimeout);
        timer.connect_output(&timerEvent);

        timeToWaitEnd.init(&actSend);

        dataFromRadio.init(&actReceivedData);

        for (uint8 var = 0; var < 9; ++var) {
            ids[var]=0;
        }

        Message message;
        message.command=Message::askForFreeId;
        prepareForSend(message);
        waitForAnswerTimer.set(500);
       timer.connect_output(&noAnswerEvent);
       noAnswerEvent.init(&actId);
}

void Application::setId(){
    id=1;
    startTimer.set(10000);
    startTimer.connect_output(&startEvent);
    startEvent.init(&actStart);

}

void Application::startRound(){
    counter=1;
    led.displayNumber(counter);
    Message messageToSend;
    messageToSend.number=counter;
    messageToSend.senderId=id;
    messageToSend.receiverId=id+1;
    messageToSend.command=Message::displayNumber;
    prepareForSend(messageToSend);
}
void Application::prepareForSend(Message message){
    Buffer* buf = new(&getApplication().pool) Buffer(&getApplication().pool);
    if(0 != buf) {
       buf->write(message);
       messagesToSend->assign(buf);
    }

}



void Application::send(){
    // todo: check if Radio is receiving data;
    // invoke internal memory management

    Buffer *buf = messagesToSend->get();
    out_sendToRadio->assign(buf);
    timeToWait=randomGenerator.next(60)+15;
}



void Application::receivedData(){
    Message message;
    Buffer *buf = (Buffer*)dataFromRadio.get();
    buf->read(message);
    buf->downRef();

    if(message.command == Message::displayNumber && message.receiverId==id){

        uint8 nextId = id+1;
        if(ids[nextId]==0){
            nextId=1;
        }
        counter=message.number;
        if(id==1){
            counter++;
        }

        led.displayNumber(counter);
        Message messageToSend;
        messageToSend.number=counter+1;
        messageToSend.senderId=id;
        messageToSend.receiverId=id+1;
        messageToSend.command=Message::displayNumber;
//        Message ackMessage;
//        messageToSend.senderId=id;
//        messageToSend.receiverId=message.senderId;
//        messageToSend.command=Message::ack;
//        buf = new(&getApplication().pool) Buffer(&getApplication().pool);
//        if(0 != buf) {
//           buf->write(ackMessage);
//            messagesToSend->assign(buf);
//        }
        prepareForSend(messageToSend);

    }

    if(message.command==Message::askForFreeId){
        uint8 newId;
        uint8 var;
        for (var = 0; var < 9; ++var) {
            if(ids[var]==0){
                newId=(ids[var-1]+1);
                ids[var]=newId;
            }
        }
        Message newMessage;
        newMessage.senderId=id;
        newMessage.command=Message::freeId;
        newMessage.receiverId=newId;
        prepareForSend(newMessage);
    }

    if(message.command==Message::freeId && id==0){
        ids[message.senderId-1]=message.senderId;
        id=message.receiverId;
        ids[id-1]=id;
    }


}



void Application::timeout()
{

    timeToWait--;
    if(timeToWait == 0){
        timeToWaitEnd.notify();
    }
//    Message message;
//    counter++;
//
//    if(counter <= 0){
//        counter = 1;
//    }
//    if(counter > 200){
//        counter = 1;
//    }
//
//
//    led.displayNumber(counter);
//    message.number = counter;
//    message.command = Message::displayNumber;

}

