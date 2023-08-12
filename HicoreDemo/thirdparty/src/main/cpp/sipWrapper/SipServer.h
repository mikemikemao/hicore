//
// Created by pirate on 2023/8/12.
//

#ifndef HICOREDEMO_SIPSERVER_H
#define HICOREDEMO_SIPSERVER_H

#include <linux/in.h>
#include <iostream>
#include "UdpServer.h"
#include "RequestsHandler.h"
#include "SipMessage.h"

class SipServer
{
public:
    SipServer(std::string ip, int port = 5060);

private:
    void onNewMessage(std::string data, sockaddr_in src);
    void onHandled(const sockaddr_in& dest, std::shared_ptr<SipMessage> message);

    UdpServer _socket;
    RequestsHandler _handler;
    SipMessageFactory _messagesFactory;
};


#endif //HICOREDEMO_SIPSERVER_H
