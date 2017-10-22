#include <iostream>
#include "protocol.h"

using namespace std;

Event receiver(frame&);


void sender(void){
	seqNo Sn = 0;
	seqNo ackNo;	//Frame No to be sent
	bool canSend = true, success;
	Event e = PACKET_AVAILABLE;
	packet temp;
	frame f, buffer;
	
	while(true){
		if(e == PACKET_AVAILABLE && canSend){
			temp = GetData();
			f = MakeFrame(Sn, temp);
			buffer = StoreFrame(f);
			e = StartTimer();
			success = SendFrame(f);
			if(e != TIMEOUT && success){
				Sn = (Sn + 1) % 2;
				e = receiver(f);
				canSend = false;
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
			seqNo ackNo = ReceiveFrame(f);
			cout<<"\n\t\t\tAckNo = "<<ackNo<<"\tSn = "<<Sn;
			if( !corrupted(f,1) && ackNo == Sn){
				StopTimer();
				PurgeFrame(Sn-1, f);
				canSend = true;
				e = PACKET_AVAILABLE;
			}
		}
		
		if(e == TIMEOUT || e == ERROR){

			StartTimer();
			//ResendFrame(Sn - 1);
			cout<<"\nTimeout or Error occured...";
			success = SendFrame(f);
			e = StartTimer();
			if(e != TIMEOUT && success){
				Sn = (Sn + 1) % 2;
				e = receiver(f);
				canSend = false;
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
Event receiver(frame &received){
	frame f;
	bool success;
	while(true){
		//WaitForEvent();
		//if(!success);
		
		if(true){	//Event(ArrivalNotification)
			f = ReceiverFrame(received);
			if(corrupted(f, 0))
				return ERROR;
			if(f.seq == Rn){
				//cout<<"\n\tEquals...";
				packet data = ExtractData(f);
				DeliverData(data);
				Rn = (Rn + 1) % 2;
			}
			//frame foo;
			success = SendFrame(f);
			if(success){
				cout<<"\nAcknowledgement Sent...";
				return FRAME_ARRIVED;
			}
			else{
				cout<<"\nAcknowledgement lost...\n";
				return ERROR;
			}

		}
	}
}

int main(void){
	sender();
	//sender();
	return 0;
}
