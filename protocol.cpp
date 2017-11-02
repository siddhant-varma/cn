#include "protocol.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

int randNum(float chance){
	int temp = rand() % 100;
	if(temp <= chance * 100){
		return 1;
	}
	else return 0;
}

packet GetData(void){
	packet p;
	cout<<"\n\nEnter Message:\t";
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
	if(randNum(.75))
		return true;
	else{
		cout<<"\n\t\t\tFrame Lost during transmission...";
		return false;
	}
}

seqNo ReceiveFrame(frame &f){
	cout<<"\nAcknowledgement Received";
	return f.ack;
}

void PurgeFrame(seqNo s, frame &f){
	if(f.seq == s){
		f.seq =  -1;
		cout<<"\nFrame Purged";
	}
	return;
} 

Event StartTimer(){
	for( ; running < MAX_TIME; running++){
		if(randNum(.6))
			return FRAME_ARRIVED;
	}
	return TIMEOUT;
}

void StopTimer(){
	running = 0;
	return;
}

//ReceiverSide
frame& ReceiverFrame(frame &fr){
	return fr;
}

packet ExtractData(frame &fr){
	cout<<"\n\t\t\t\t\t\tExtracting Frame...";
	return fr.info;
}

void DeliverData(packet &p){
	cout<<"\n\t\t\t\t\t\tPacket successfully delivered to NL.\n";
	cout<<"\n\t\t\t\t\t\tMessage:\t"<<p.data<<endl;
	return;
}

bool SendAck(frame &f){
	f.ack = (f.seq + 1) % 2;
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
		cout<<"\n\t\t\tAcknowledgement Lost during transmission...\n";
		return false;
	}
}

bool corrupted(frame &fr, int a){
	if(randNum(.8))
		return false;
	else return true;
}