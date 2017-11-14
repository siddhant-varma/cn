#include<iostream>
#include<cstdio>
#include<cstdlib>
#define inc(k) k = 1 - k;
using namespace std;
typedef unsigned int seq_nr;
typedef int packet;
typedef enum{frame_arrival,cksum_err,timeout} event_type;
int i=0;
//typedef struct{unsigned char data[MAX_PKT];} packet;
//typedef enum{data,ack,nak} frame_kind;
typedef struct{
	seq_nr seq;
	seq_nr ack;
	packet info;
}frame;

frame data;

void wait_for_eventsen(event_type *event)
{
	int temp=rand() % 10;
	if(temp>=0&&temp<8)
	{
		 *event=frame_arrival;
		 cout<<"\tReceiver:Acknowledgement Sent";
	}
	else
	{
		 *event=cksum_err;
		 cout<<"\tReceiver:Garbled Data";
		 cout<<"\n\tSender:Timeout";
	}
}
void wait_for_eventrec(event_type *event)
{
	int temp=rand() % 8;
	if(temp>=0&&temp<5)
	{
		 *event=frame_arrival;
		 cout<<"\n\tSender:Acknowledgement Recieved";
	}
	else if(temp>=5&&temp<7)
	{
		 *event=cksum_err;
		 cout<<"\n\tSender:No Acknowledgement Recieved";
	}
	else
	{
		*event=timeout;
		cout<<"\n\tSender:Timeout";
	}
}
void from_network_layer(packet *p)
{
	*p=i++;
}
void to_physical_layer(frame *s)
{
	data=*s;
	//cout<<"\nData Sent,Packet Number:"<<s->info;
	//cout<<"Seq no.:"<<s->seq;
}
void from_physical_layer(frame *r)
{
	*r=data;
}
void to_network_layer(packet *p)
{
	data.info=*p;
}
//#define inc(k) if(k<MAX_SEQ) k=k+1;else k=0
