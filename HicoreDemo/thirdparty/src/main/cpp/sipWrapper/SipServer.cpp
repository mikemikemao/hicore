//
// Created by pirate on 2023/8/12.
//

#include "SipServer.h"

SipServer::SipServer(std::string ip, int port) :
        _socket(ip, port, std::bind(&SipServer::onNewMessage, this, std::placeholders::_1, std::placeholders::_2)),
        _handler(ip, port, std::bind(&SipServer::onHandled, this, std::placeholders::_1, std::placeholders::_2))
{
    _socket.startReceive();
}


void SipServer::onNewMessage(std::string data, sockaddr_in src)
{
    auto message = _messagesFactory.createMessage(std::move(data), std::move(src));
    if (message.has_value())
    {
        _handler.handle(std::move(message.value()));
    }
}