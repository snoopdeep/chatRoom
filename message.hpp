#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdlib>
#include <cstring>
#include <cstdio>

class Message {
    public: 
        Message() : bodyLength_(0) {}
        
        enum {maxBytes = 512};
        enum {header = 4};

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

    private: 
        char data[header+maxBytes];
        size_t bodyLength_;
};

#endif MESSAGE_HPP