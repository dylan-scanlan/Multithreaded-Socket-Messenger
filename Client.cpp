#include "socket.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace Sync;
using namespace std;

int main(void)
{
	bool run = true;
	Socket cSock("127.0.0.1",2000); 
	cSock.Open();
	string input;
	

	cout << "I am a client" << endl;
	cout << "Type <exit> to close the connection"<<endl;

	while(run==true){
		cout<<"Enter a message: ";
		cin>>input;
		if(input=="exit"){
			break;
		}
		ByteArray bArray (input);
		cSock.Write(bArray);
		ByteArray returned("");
		int readSuccess = cSock.Read(returned);
		if(readSuccess == 0){
			cout<<"Server has disconnected"<<endl;
			break;
		}
		string newMessage = returned.ToString();
		cout<<"New massage: "<<newMessage<<endl;
	}
	cSock.Close();
	cout<<"Connection closed"<<endl;
}
