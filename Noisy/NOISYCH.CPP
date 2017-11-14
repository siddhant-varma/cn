#define MAX_SEQ 1
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include "protocol.h"

using namespace std;

void reciever();
void sender()
{
	seq_nr next_frame_to_send;
	frame s;
	packet buffer;
	event_type event;
	next_frame_to_send=0;
	from_network_layer(&buffer);	//Increments value in packet sequentially
	while(true)
	{
		s.info=buffer;
		s.seq=next_frame_to_send;
		cout<<"\n\nData Sent,Packet Number:"<<s.info;
		cout<<"\tSeq no.:"<<s.seq;
		to_physical_layer(&s);	//	Saves frame s into frame data
		wait_for_eventsen(&event);	//	returns event frame_arrival or cksum_err
		if(event==frame_arrival)
		{
			reciever();
			from_physical_layer(&s);	//	Saves frame s into frame data
			if(s.ack==next_frame_to_send)
			{
				from_network_layer(&buffer);
				inc(next_frame_to_send);	//	Increments Sn or next_frame_to_send
			}
		}
		sleep(5);
	}
}
void reciever()
{
	seq_nr frame_expected;
	frame r,s;
	event_type event;
	frame_expected=0;
	wait_for_eventrec(&event);	//	returns ACK event for sender
	if(event==frame_arrival)
		{
			from_physical_layer(&r);
			if(r.seq==frame_expected)
			{
				to_network_layer(&r.info);
				inc(frame_expected);
			}
			s.ack=1-frame_expected;
			to_physical_layer(&s);
		}
}
int main(void)
{
	sender();
}
