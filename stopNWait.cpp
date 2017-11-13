#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "protocol.h"

using namespace std;

frame receiver(frame);

void sender(void){
	seqNo Sn = 0;
	seqNo ackNo;	//Frame No to be sent
	bool canSend = true, success;
	Event e = PACKET_AVAILABLE;
	packet tep;
	frame f, buffer, temp;
	
	while(true){
		if(e == PACKET_AVAILABLE && canSend){
			tep = GetData();
			f = MakeFrame(Sn, tep);
			buffer = StoreFrame(f);
			e = StartTimer();
			success = SendFrame(f);
			if(e != TIMEOUT && success){
				Sn = (Sn + 1) % 2;
				temp = receiver(f);	// returns FRAME_ARRIVED on succesful arrival of ACK
				canSend = false;
				if(temp.ack > -1)
					e = FRAME_ARRIVED;
				else
					e = ERROR;
			}
			else if(!success){
				e = ERROR;
			}
		}
		//WaitForEvent(); //StartTimer() does the work.
		if(e == FRAME_ARRIVED){
			seqNo ackNo = ReceiveFrame(temp);	// Outputs Acknowledgement Recevied
			cout<<"\n\t\t\tAckNo = "<<ackNo<<"\tSn = "<<Sn;
			if( !corrupted(temp,1) && ackNo == Sn){
				StopTimer();
				PurgeFrame(Sn-1, buffer);
				canSend = true;
				e = PACKET_AVAILABLE;
			}
			else{
				cout<<"\nAcknowldegement Corrupted...\n";
				e = ERROR;
			}
		}
		
		if(e == TIMEOUT || e == ERROR){
			Sn = abs(Sn-1);

			StartTimer();
			//Does the work of ResendFrame(Sn - 1);
			cout<<"\n\t\t\tTimeout or Error occured...\n";
			success = SendFrame(f);
			e = StartTimer();
			if(e != TIMEOUT && success){
				Sn = (Sn + 1) % 2;
				f = receiver(f);
				canSend = false;
				if(f.ack > -1)
					e = FRAME_ARRIVED;
				else
					e = ERROR;
			}			
			else if(!success){
				e = ERROR;
			}
		}
	}
}

seqNo Rn = 0;
frame receiver(frame received){
	frame f;
	bool success;
	while(true){
		//WaitForEvent();		
		if(true){	//Event(ArrivalNotification)
			f = ReceiverFrame(received);
			if(corrupted(f, 0)){
				f.ack = -1;
				return f;
			}
			if(f.seq == Rn){
				packet data = ExtractData(f);	//Outputs Extracting Frame
				DeliverData(data);
				Rn = (Rn + 1) % 2;
			}

			success = SendAck(f);	//Returns true for successful delivery of Ack
			if(success)
				cout<<"\n\t\t\t\t\t\tAcknowledgement Sent...";
			else
				f.ack = -1;

			return f;

		}
	}
}

int main(void){
	sender();
	return 0;
}