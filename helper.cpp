#include "helper.h"
#include<iostream>
#include<string>
#include<functional>
#include<unordered_map>
#include<memory>


//method that sends the message to the receiver
void Sender::sendMessage(std::string message, int x, int y, ReceiverClass* receiver, Receiver* d, SenderClass* sender){
    Message msg;
    msg.message = message;
    msg.num1  = x;
    msg.num2 = y;
    msg.receiver = receiver;
//check to see if the receiver is in the list of receivers of the message
    auto finder = messageReceivers.find(receiver);
    if(messageReceivers.end()!=finder)
        d->receiveMessage(msg, this);
    else
        std::cout<<"Does not respond to the message";
        
    
}

void Sender::addReceiver(std::string message, ReceiverClass* receiver){
    messageReceivers[receiver]=message;
}


void Receiver::receiveMessage(Message msg, Sender* sender){
    auto finder = messageToFunction.find(msg.message);
    if(messageToFunction.end()!=finder){
//call the method associated with the message with the arguments from the received message
        auto ret = finder->second(msg.num1, msg.num2);
//return value is stored in the variable accessed by the shared pointer
        this->returnval = ret;
        
    }
}



void Receiver::addMethod(std::string message, std::function<int(int, int)> func){
    messageToFunction[message]=func;
}















