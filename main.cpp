/* Vinay Daniel Washington
U00882938 - washington.123@wright.edu*/

#include "helper.h"
#include<iostream>
#include<string>
#include<functional>
#include<unordered_map>
#include<memory>




class SenderClass{
    std::shared_ptr<Receiver> r = std::make_shared<Receiver>();
public:
    Sender sender;
//call to the sendMessage of the Sender    
    void send(std::string message, int x, int y, ReceiverClass* receiver, Receiver* r){
        sender.sendMessage(message, x, y, receiver, r, this);
        std::cout<<"The return value is "<<r->returnval<<"\n";
    }

};

class ReceiverClass{
public:
    Receiver receiver;
    std::string message;


};

class AdditionClass: public ReceiverClass{
public:
    Receiver receiver;
    std::string message;
    AdditionClass(std::string message){
        this->message = message;
    }
    void listenerAdder( Sender* sender){
//adding the receiver and method associated with the message "sub"
    sender->addReceiver(message, this);
    receiver.addMethod(message, add1());
    
}
    struct add1{
    int operator()(int a, int b){
        return a+b;
        }
    };
};

class SubtractionClass: public ReceiverClass{
public:
    Receiver receiver;
    std::string message;
    SubtractionClass(std::string message){
        this->message = message;
    }
    void listenerAdder( Sender* sender){
//adding the receiver and method associated with the message "sub"
    sender->addReceiver(message, this);
    receiver.addMethod(message, sub());
    
}
    struct sub{
    int operator()(int a, int b){
        return a-b;
        }
    };
};

class MultiplicationClass: public ReceiverClass{
public:
    Receiver receiver;
    std::string message;
    MultiplicationClass(std::string message){
        this->message = message;
    }
    void listenerAdder( Sender* sender){
//adding the receiver of the message "mul"
    sender->addReceiver(message, this);
//adding another receiver of another message "div" to the same class
    sender->addReceiver("div", this);
//adding the methods associated with the messages
    receiver.addMethod(message, mul());
    receiver.addMethod("div", div());
    
    
}
    struct mul{
    int operator()(int a, int b){
        return a*b;
        }
    };
    struct div{
    int operator()(int a, int b){
        return a/b;
        }
    };
};


int main(int argc, const char *argv[]){
    AdditionClass* addition = new AdditionClass("add");
    SubtractionClass* sub = new SubtractionClass("sub");
    MultiplicationClass* mul = new MultiplicationClass("mul");
    SenderClass* sender = new SenderClass();
//call to listenerAdder which adds the receiver to the list of receivers of the message
    addition->listenerAdder(&sender->sender);
    sub->listenerAdder(&sender->sender);
    mul->listenerAdder(&sender->sender);
    std::cout<<"Addition Class:"<<"\t\t";
//sending message to AdditionClass
    sender->send("add", 10, 20, addition, &addition->receiver);    
//sending message to SubtractionClass
    std::cout<<"Subtraction Class:"<<"\t";
    sender->send("sub", 50,40, sub,  &sub->receiver);
//sending message to MultiplicationClass (function mul)
    std::cout<<"Multiplication Class   mul function:"<<"\t";
    sender->send("mul", 10,5, mul,  &mul->receiver);
//sending message to MultiplicationClass (function div)
    std::cout<<"Multiplication Class   div function:"<<"\t";
    sender->send("div", 8,4, mul,  &mul->receiver);
}

