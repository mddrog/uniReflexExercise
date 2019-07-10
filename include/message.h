/*
 * Application.h
 *
 *  Created on: 01.04.2018
 *      Author: Hannes Menzel
 */

#ifndef MESSAGE_H
#define MESSAGE_H

//#include "conf.h"
#include "reflex/types.h"

namespace reflex {

class Message {

public:

    enum Command{
        freeId = 1,
        ack = 2,
        noAck = 3,
        displayNumber = 4,
        askForFreeId = 5,
    };
    Command command;
    uint8 senderId;
    uint8 receiverId;
    uint8 number;
    };
}

#endif /* MESSAGE_H */
