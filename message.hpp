#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

/* 
header is of 4 bytes and maxBytes can be stored as 512 bytes
header stores the body length that is the current body length
data stores the header+bodyLength with maximum size of header+maxBytes

client attempts to send message:- It will encode header and put message into the data and send data
server gets the message, decodes the header, get the bodylength from the header and hence complete body
then server sends the message to all the clients connected to that room.
*/


class Message {
    public: 
        Message() : bodyLength_(0) {}
        
        enum {maxBytes = 512};
        enum {header = 4};

        Message(std::string message){
            bodyLength_ = getNewBodyLength(message.size());
            encodeHeader();
            std::memcpy(data + header, message.c_str(), bodyLength_);
        };

        void printMessage(){
            char* message = getData();
            std::string s(message);
            std::cout<<"Message recieved: "<<s<<std::endl;
        }

        char* getData(){
            int length = header + bodyLength_;
            char result[length+1] = "";
            strncpy(result, data, length);
            return result;
        }

        char* getBody(){
            char* data = getData();
            char result[bodyLength_+1] = "";
            strncpy(result, data+header, bodyLength_); 
            return result;
        }

        size_t getNewBodyLength(size_t newLength){
            if(newLength > maxBytes){
                return maxBytes;
            }
            return newLength;
        }

        void encodeHeader(){
            char new_header[header+1] = "";
            sprintf(new_header, "%4d", static_cast<int>(bodyLength_));
            memcpy(data, new_header, header);
        }
        
        bool decodeHeader(){
            char new_header[header+1] = "";
            strncat(new_header, data, header);
            int header = atoi(new_header);
            if(header>maxBytes){
                bodyLength_ = 0;
                return false;
            }
            bodyLength_ = header;
            return true;
        }

        size_t getBodyLength(){
            return bodyLength_;
        }

    private: 
        char data[header+maxBytes];
        size_t bodyLength_;
};

#endif MESSAGE_HPP