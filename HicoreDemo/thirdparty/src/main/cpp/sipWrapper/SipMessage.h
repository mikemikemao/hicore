//
// Created by pirate on 2023/8/12.
//

#ifndef HICOREDEMO_SIPMESSAGE_H
#define HICOREDEMO_SIPMESSAGE_H
#include <iostream>
#include <linux/in.h>

class SipMessage {
public:
    SipMessage(std::string message, sockaddr_in src);

protected:
    virtual void parse();
    bool isValidMessage() const;
    std::string extractNumber(std::string header) const;

    std::string _type;
    std::string _header;
    std::string _via;
    std::string _from;
    std::string _fromNumber;
    std::string _to;
    std::string _toNumber;
    std::string _callID;
    std::string _cSeq;
    std::string _contact;
    std::string _contactNumber;
    std::string _contentLength;
    std::string _messageStr;

    sockaddr_in _src;
};


#endif //HICOREDEMO_SIPMESSAGE_H
