#include <iostream>

#ifndef CHATROOM_HPP
#define CHATROOM_HPP

#include "message.hpp"
#include <deque>
#include <set>
#include <memory>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Participant {
    public: 
        void deliver(Message& message);
};

typedef std::shared_ptr<Participant> ParticipantPointer;

class Room{
    public:
        void join(ParticipantPointer participant);
        void leave(ParticipantPointer participant);
        void deliver(Message& message);
    private:
        std::deque<Message> messageQueue;
        enum {maxParticipants = 100};
        std::set<ParticipantPointer> participants;
};

class Session: public Participant, std::enable_shared_from_this<Session>{
    public:
        Session(tcp::socket s, Room &room);
        void start();
        void deliver(Message& message);
        char* readHeader();
        char* readBody();
        void write();
    private:
        tcp::socket clientSocket;
        Room& room;
        Message& message;
        std::deque<Message> messageQueue; 
};

#endif CHATROOM_HPP