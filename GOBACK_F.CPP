# include <iostream>
# include <conio.h>
# include <cstdlib>
# include <time.h>
# include <math.h>

using namespace std;

int wind;	//	window size
int fr_send_at_instance;	// Frame Outstanding Count
int *arr1;		//Frame Array
int sw=0, rw=0; // tells expected frame:	sender window, receiver window
void reciever();

void sender()
{
	
 for (int i = sw, j = 0 ; i < sw + fr_send_at_instance ; i++, j++)
 {
  arr1[j]=i % wind;
  cout << " SENDER   : Frame " <<arr1[j]<< " is sent\n";
 }
 reciever ();
}

void reciever()
{
	time_t t;
	int prob;	// Probability of frames getting lost
	int f1;
	int a1;		// Probability for ACK
	char ch;

	srand((unsigned) time(&t));
	prob = rand() % 10;		// Chance of frame getting garbageled is 1/10 .

   // if f= 5 frame is discarded for some reason
   // else they are correctly recieved

	if (prob != 5)	// Frame Received Correctly	
	{
		for (int i = 0 ; i < fr_send_at_instance ; i++)
		{
			if (rw == arr1[i])	//Value of frame array is the frame expected by receiver
			{
				cout << "RECIEVER : Frame " << arr1[i] << " recieved correctly\n";
				rw = (rw + 1) % wind;
			}
			else
				cout << "RECIEVER : Duplicate frame " << arr1[i] << " discarded\n";
		}
		a1 = rand() % (3 * wind);	//	Probability of ACK getting lost are 1/3.

	   // if a1 belongs to 0 to 3 then
	   //     all ack after this (incl this one) lost
	   // else
	   //     all recieved

		if (a1 >= 0 && a1 <= fr_send_at_instance)	// If probability for ACK getting lost, lies in sliding window range, all ACK are lost.
		{
			cout << "(Acknowledgement " << arr1[a1] << " & all after this lost)\n";
			sw = arr1[a1];	//	Resetting sender window counter to the last frame ACK lost <- Implementing GO BACK N
		}
		else{
			cout << "(Acknowledgement " << arr1[a1] << " & all after are received)\n";
			sw = (sw + fr_send_at_instance) % wind;	//	Sliding the sender window for next cycle accordingly
		}
			
	}
	else	// Frame Lost.
	{
		f1 = rand() % fr_send_at_instance;

  		// f1 gives index of the frame being lost

		for (int i = 0 ; i < f1 ; i++)	//	If frame is less than f1, then receive correctly
		{
			if (rw == arr1[i])	//	Frame Expected
			{
				cout << " RECIEVER : Frame " << arr1[i] << " recieved correctly\n";
				rw = (rw + 1) % wind;	//	Sliding  Receiver Window on successful frame receive
			}
			else	//	Duplicate Frame received
				cout << " RECIEVER : Duplicate frame " << arr1[i] << " discarded\n";
		}
		
		int ld = rand() % 2;	//	Decieds if frame is damaged(corrupted) or lost.		
		// ld == 0 frame damaged
		// else frame lost
		if (ld == 0)
			cout << " RECIEVER : Frame " << arr1[f1] << " damaged\n";
		else
			cout << "            (Frame " << arr1[f1] << " lost)\n";

		for (int i = f1 + 1 ; i < fr_send_at_instance ; i++)	//	All frames after target damaged fram - f1 are discarded as they are duplicates.
			cout << " RECIEVER : Frame " << arr1[i] << " discarded\n";

		cout << " (SENDER TIMEOUTS --> RESEND THE FRAME)\n";	// For frame f1, it had been garbageled so there will be an Timeout

		sw = arr1[f1];	//	Sliding the sender window for next cycle accordingly
	}
	cout << "Want to continue...(Y/N): ";
	cin >> ch;

	if (ch == 'y'||ch=='Y')
		sender();
	else
		exit(0);
}

int main()
{
	cout<<"Enter Window Size:\t";
	cin>>wind;
	fr_send_at_instance=wind - 1;
	arr1 = new int[fr_send_at_instance];
	sender();
	getch();
}
