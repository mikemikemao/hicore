//
// Created by pirate on 2023/8/12.
//

#ifndef HICOREDEMO_SIPMESSAGEFACTORY_H
#define HICOREDEMO_SIPMESSAGEFACTORY_H
#include <optional>
#include <memory>
#include <linux/in.h>
#include "SipMessage.h"
#include <iostream>

class SipMessageFactory {
public:
    std::optional<std::shared_ptr<SipMessage>> createMessage(std::string message, sockaddr_in src);

private:
    static constexpr auto SDP_CONTENT_TYPE = "application/sdp";

    bool containsSdp(const std::string& message) const;
};


#endif //HICOREDEMO_SIPMESSAGEFACTORY_H
