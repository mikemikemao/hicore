//
// Created by pirate on 2023/8/12.
//

#ifndef HICOREDEMO_REQUESTSHANDLER_H
#define HICOREDEMO_REQUESTSHANDLER_H

#include <linux/in.h>
#include <iostream>
#include <unordered_map>

class RequestsHandler {
public:
    using OnHandledEvent = std::function<void(const sockaddr_in&, std::shared_ptr<SipMessage>)>;

    RequestsHandler(std::string serverIp, int serverPort,
                    OnHandledEvent onHandledEvent);
private:
    void initHandlers();



    std::unordered_map<std::string, std::function<void(std::shared_ptr<SipMessage> request)>> _handlers;
    std::unordered_map<std::string, std::shared_ptr<Session>> _sessions;
    std::unordered_map<std::string, std::shared_ptr<SipClient>> _clients;

    std::function<void(std::shared_ptr<SipClient>)> _onNewClient;
    std::function<void(std::shared_ptr<SipClient>)> _onUnregister;

    OnHandledEvent _onHandled;
    std::string _serverIp;
    int _serverPort;
};


#endif //HICOREDEMO_REQUESTSHANDLER_H
