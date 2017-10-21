#include <iostream>
#include "protocol.h"

using namespace std;

int main(void){
	
	int Sn = 0;
	bool canSend = true;
	
	while(true){
		if(Event (RequestToSend) && canSend){
			GetData();
			MakeFrame(Sn);
			StoreFrame(Sn);
			SendFrame(Sn);
			StartTimer();
			Sn++;
			canSend = false;
		}
		
		WaitForEvent();
		if(Event (ArrivalNotification) ){
			ReceiveFrame(ackNo);
			if( ! corrupted && ackNo == Sn){
				StopTime();
				PurgeFrame(Sn-1);
				canSend = true;
			}
		}
		
		if(Event(TimeOut)){
			StarTimer();
			ResendFrame(Sn - 1);
		}
	}
	
	return 0;
}
