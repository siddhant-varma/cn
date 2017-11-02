#include <iostream>
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
		
		/*if(success && e == FRAME_ARRIVED){
			e = receiver(f);
		}*/
		//WaitForEvent(); //StartTimer() does the work.
		if(e == FRAME_ARRIVED){
			//cout<<"\nAcknowledgement received.";
			seqNo ackNo = ReceiveFrame(temp);
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

			StartTimer();
			//ResendFrame(Sn - 1);
			cout<<"\n\t\t\tTimeout or Error occured...\n";
			success = SendFrame(f);
			e = StartTimer();
			if(e != TIMEOUT && success){
				//Sn = (Sn + 1) % 2;
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
		
		/*if(success && e == FRAME_ARRIVED){
			e = receiver(f);
		}*/
		}
	}	
//}

seqNo Rn = 0;
frame receiver(frame received){
	frame f;
	bool success;
	while(true){
		//WaitForEvent();
		//if(!success);
		
		if(true){	//Event(ArrivalNotification)
			f = ReceiverFrame(received);
			if(corrupted(f, 0)){
				f.ack = -1;
				//return ERROR;
			}
			if(f.seq == Rn){
				//cout<<"\n\tEquals...";
				packet data = ExtractData(f);
				DeliverData(data);
				Rn = (Rn + 1) % 2;
			}
			//frame foo;
			success = SendAck(f);
			if(success){
				cout<<"\n\t\t\t\t\t\tAcknowledgement Sent...";
				//return FRAME_ARRIVED;
				
			}
			else{
				f.ack = -1;
				//cout<<"\n\t\t\t\t\t\tAcknowledgement lost...\n";
				//return ERROR;
			}
			return f;

		}
	}
}

int main(void){
	sender();
	//sender();
	return 0;
}
