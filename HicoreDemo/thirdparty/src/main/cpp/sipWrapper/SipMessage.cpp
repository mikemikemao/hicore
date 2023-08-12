//
// Created by pirate on 2023/8/12.
//

#include "SipMessage.h"

SipMessage::SipMessage(std::string message, sockaddr_in src)
           : _messageStr(std::move(message)), _src(std::move(src))
{
    parse();
}
