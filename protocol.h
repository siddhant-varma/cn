#ifndef PROTOCOL
#define PROTOCOL

typedef int seqNo;	//Sequence Number

typedef enum{
	PACKET_AVAILABLE,	//Triggers when NL sends packet
	FRAME_ARRIVED,
	ERROR,
	TIMEOUT
} Event;

typedef struct{
	char data[20];		//Data contained in and as packet
} packet;

typedef struct{
	seqNo seq;
	seqNo ack;		//Acknowledge Number
	packet info;
} frame;			//Frame structure comprising packet strucutre

int randNum(float);	//Generates Random number and returns accordingly boolean with chance passed as parameter

packet GetData(void);

frame MakeFrame(seqNo, packet);

frame StoreFrame(frame);

bool SendFrame(frame&);

//void ToPhysicalLayer(frame&);

bool OverTransmissionMedia(frame&);

seqNo ReceiveFrame(frame&);

void PurgeFrame(seqNo, frame&);

static int MAX_TIME = 100;
static int running = 0;
Event StartTimer();
void StopTimer();

//ReceiverSide

frame& ReceiverFrame(frame&);

packet ExtractData(frame&);

void DeliverData(packet&);

bool corrupted(frame&, int);
#endif
