//
// Created by maochaoqun on 2023/8/13.
//

#ifndef HICOREDEMO_SIPSDPMESSAGE_H
#define HICOREDEMO_SIPSDPMESSAGE_H


#include "SipMessage.h"
#include <iostream>
class SipSdpMessage : public SipMessage{
public:
    SipSdpMessage(std::string message, sockaddr_in src);
};


#endif //HICOREDEMO_SIPSDPMESSAGE_H
