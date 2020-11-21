//
// Created by shi on 2020/11/21.
//

#ifndef CHAT_DEMO_CHAT_SESSION_H
#define CHAT_DEMO_CHAT_SESSION_H

#include <boost/asio.hpp>

#include "chat_message.hpp"
#include "chat_room.hpp"
#include "chat_participant.h"

namespace shi {
    class ChatSession
            : public ChatParticipant
            , public std::enable_shared_from_this<ChatSession>
    {
    public:
        ChatSession(boost::asio::ip::tcp::socket socket, ChatRoom& room);
        void start();
        void deliver(const ChatMessage& msg) override;

    private:
        void doReadHeader();
        void doReadBody();
        void doWrite();

    private:
        boost::asio::ip::tcp::socket socket_;
        ChatRoom& room_;
        ChatMessage read_msg_;
        ChatMessageQueue write_msgs_;
    };
}


#endif //CHAT_DEMO_CHAT_SESSION_H
