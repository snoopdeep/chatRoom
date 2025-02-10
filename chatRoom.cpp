#include "chatRoom.hpp"

void Room::join(ParticipantPointer participant){
    this->participants.insert(participant);
}

void Room::leave(ParticipantPointer participant){
    this->participants.erase(participant);
}

void Room::deliver(Message &message){
    for(ParticipantPointer participant: this->participants){
        participant->deliver(message);
    }
}

void Session::start(){
    room.join();
}

Session::Session(tcp::socket s, Room& r): clientSocket(std::move(s)), room(r){};

char* Session::readHeader(){

}

char* Session::readBody(){

}

void Session::deliver(Message& message){
    
}










int main(int argc, char* argv[]){

}