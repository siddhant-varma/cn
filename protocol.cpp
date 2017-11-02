#include "protocol.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

int randNum(float chance){
	//srand(0);
	int temp = rand() % 100;
	//cout<<"\n\t\t\tRandom Num = "<<temp;
	if(temp <= chance * 100){
		return 1;
	}
	else return 0;
	//return temp;
}

packet GetData(void){
	packet p;
	cout<<"\nEnter Message:\t";
	cin>>p.data;
	return p;
}

frame MakeFrame(seqNo n, packet p){
	cout<<"\nMaking Frame...";
	frame f;
	f.seq = n;
	f.info = p;
	return f;
}

frame StoreFrame(frame f){
	cout<<"\nStoring Frame...";
	return f;
}

bool SendFrame(frame &f){
	cout<<"\nSending Frame...";
	/*return ToPhysicalLayer(f);
}
bool ToPhysicalLayer(frame &f){
	return OverTransmissionMedia(f);
}
bool OverTransmissionMedia(frame &f){*/
	if(randNum(.75)){
		//f.ack = (f.seq + 1) % 2;//for receiver side SendFrame()
		return true;
	}
	else{
		cout<<"\n\t\t\tFrame Lost during transmission...";
		return false;
	}
}

/*void WaitForEvent(Event &e){

}*/
seqNo ReceiveFrame(frame &f){
	cout<<"\n\t\t\t\t\tAcknowledgement Received";
	return f.ack;
}

void PurgeFrame(seqNo s, frame &f){
	if(f.seq == s){
		f.seq =  -1;
		cout<<"\nFrame Purged";
	}
	return;
} 

//static int MAX_TIME = 100;
//static int running = 0;
Event StartTimer(){
	//cout<<"\n\t\t\tTimer Running...";
	for( ; running < MAX_TIME; running++){
		//cout<<"\t"<<running;
		//Sleep(.1);
		if(randNum(.6))
			return FRAME_ARRIVED;
	}
	//cout<<"\n\t\t\tTimer TimeOut";
	return TIMEOUT;
}

void StopTimer(){
	running = 0;
	//cout<<"\n\t\t\tTimer stopped...";
	return;
}

//ReceiverSide
frame& ReceiverFrame(frame &fr){
	//cout<<"\n\t\t\t\t\t\tIn ReceiveFrame()..."<<fr.seq;
	return fr;
}

packet ExtractData(frame &fr){
	cout<<"\n\t\t\t\t\tExtracting Frame...";
	return fr.info;
}

void DeliverData(packet &p){
	cout<<"\n\t\t\t\t\tPacket successfully delivered to NL.";
	cout<<"\n\t\t\t\t\tMessage:\t"<<p.data;
	return;
}

bool SendAck(frame &f){
	f.ack = (f.seq + 1) % 2;//for receiver side SendFrame()
	cout<<"\nSending Acknowledgement...";
	/*return ToPhysicalLayer(f);
}
bool ToPhysicalLayer(frame &f){
	return OverTransmissionMedia(f);
}
bool OverTransmissionMedia(frame &f){*/
	if(randNum(.75)){
		cout<<"\n\t\t\t\t\t\tAcknowledgement is :\t"<<f.ack;
		return true;
	}
	else{
		cout<<"\n\t\t\tAcknowledgement Lost during transmission...";
		return false;
	}
}


bool corrupted(frame &fr, int a){
	/*if(a)
		cout<<"\nAcknowledgement ";
	else
		cout<<"\nFrame ";*/
	if(randNum(.8)){
		//cout<<"Not Corrupted.\n";
		return false;
	}
	else{
		//cout<<"Corrupted...\n";
		return true;
	}
}
