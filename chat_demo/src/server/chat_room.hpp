//
// Created by shi on 2020/11/21.
//

#ifndef CHAT_DEMO_CHAT_ROOM_HPP
#define CHAT_DEMO_CHAT_ROOM_HPP

#include <iostream>
#include <set>
#include <deque>
#include <boost/format.hpp>

#include "chat_message.hpp"
#include "chat_participant.h"

namespace shi {
    typedef  std::deque<ChatMessage> ChatMessageQueue;
    class ChatRoom
    {
    public:
        void join(const ChatParticipantPtr& participant)
        {
            std::cout << "\n====>>>> 新成员加入聊天室\n";
            participants_.insert(participant);
            for (auto& msg : recent_msgs_)
                participant->deliver(msg);
        }

        void leave(const ChatParticipantPtr& participant)
        {
            boost::format fmt("\n====>>>> 新成员离开聊天室%1%\n");
            std::cout << fmt % "<<<<====";
            participants_.erase(participant);
        }

        void deliver(const ChatMessage& msg)
        {
            std::cout << "\n====>>>> 转发新消息:" << msg.body() << '\n';
            recent_msgs_.push_back(msg);
            while (recent_msgs_.size() > max_recent_msgs)
                recent_msgs_.pop_front();

            for (auto& participant : participants_)
                participant->deliver(msg);
        }

    private:
        std::set<ChatParticipantPtr> participants_;
        enum { max_recent_msgs = 100 };
        ChatMessageQueue recent_msgs_;
    };
}

#endif //CHAT_DEMO_CHAT_ROOM_HPP
