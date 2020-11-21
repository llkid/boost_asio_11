//
// Created by shi on 2020/11/21.
//

#ifndef CHAT_DEMO_CHAT_PARTICIPANT_H
#define CHAT_DEMO_CHAT_PARTICIPANT_H

#include <memory>

#include "chat_message.hpp"

namespace shi {
class ChatParticipant
{
public:
    virtual ~ChatParticipant() = default;
    virtual void deliver(const ChatMessage& msg) = 0;
};

    typedef  std::shared_ptr<ChatParticipant> ChatParticipantPtr;
}

#endif //CHAT_DEMO_CHAT_PARTICIPANT_H
