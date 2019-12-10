#pragma once

#include<iostream>
#include<string>
#include<functional>
#include<unordered_map>
#include<memory>

class Receiver;
class Sender;
class ReceiverClass;
class SenderClass;

//structure that encapsulates all the attributes of a message (message, arguments, receiver)
struct Message{
    std::string message;
    int num1;
    int num2;
    ReceiverClass * receiver;

};



class Sender{
public:
    std::unordered_map<ReceiverClass*, std::string> messageReceivers;
    void sendMessage(std::string message, int x, int y, ReceiverClass* r, Receiver* d, SenderClass* sender);
    void addReceiver(std::string message, ReceiverClass* receiver);

    
    
};

class Receiver{
public:
    int returnval;
    std::string message;
//O(1)  datastructure that stores the mapping of messages and methods (only one type of function is being stored as of now)
    std::unordered_map<std::string, std::function<int(int, int)>> messageToFunction;
    void addMethod(std::string message, std::function<int(int, int)> func);
    void receiveMessage(Message message, Sender* sender);


};