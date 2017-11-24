#include "thread.h"
#include "socketserver.h"
#include "socket.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>
#include <string>
#include <iostream>

using namespace Sync;
using namespace std;
bool run = true;

void serveFunction(Socket sSock){
    cout<<"New client connection"<<endl;
    while(run){
        ByteArray received("");
        int readSuccess = sSock.Read(received);
        if(readSuccess == 0){
            break;
            cout<<"Client has disconnected"<<endl;
		}
        string message = received.ToString();
        for(int i=0; i<message.length(); i+=2){
            message[i] = toupper(message[i]);
        }
        ByteArray newbArray (message);
        sSock.Write(newbArray);
    }
    sSock.Close();
    cout<<"Connection closed"<<endl;
} 
void waitSignal(SocketServer *sServer){
    string input = "";
    while(run){
        cin>>input;
        if(input=="exit"){
            run=false;
            sServer->Shutdown();
        }
    }
}  

int main(void)
{
    cout << "I am a server." << endl;
    cout<< "Type <exit> to close server"<<endl;
    SocketServer sServer(2000);
    thread w(waitSignal, &sServer);
    w.detach();

    while(run){
        try{
            Socket sSock = sServer.Accept();
            thread t(serveFunction, sSock);
            t.detach();
        }
        catch(TerminationException){
            cout<<"Shutdown activated"<<endl;
            break;
        }
        
    }
    cout<<"Server closed"<<endl;
}
