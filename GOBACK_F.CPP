# include <iostream>
# include <conio.h>
# include <cstdlib>
# include <time.h>
# include <math.h>

using namespace std;

const int wind=8;
const int fr_send_at_instance=wind/2;
int arr1[fr_send_at_instance];
int sw=0, rw=0; // tells expected frame
void reciever();

void sender()
{
 int j = 0;

 for (int i = sw ; i < sw + fr_send_at_instance ; i++)
 {
  arr1[j]=i % wind;
  cout << " SENDER   : Frame " <<arr1[j]<< " is sent\n";
  j++;
 }
 reciever ();
}

void reciever()
{
	time_t t;
	int f;
	int f1;
	int a1;
	char ch;

	srand((unsigned) time(&t));
	f = rand() % 10;

   // if f= 5 frame is discarded for some reason
   // else they are correctly recieved

	if (f != 5)
	{
		for (int i = 0 ; i < fr_send_at_instance ; i++)
		{
			if (rw == arr1[i])
			{
				cout << "RECIEVER : Frame " << arr1[i] << " recieved correctly\n";
				rw = (rw + 1) % wind;
			}
			else
				cout << "RECIEVER : Duplicate frame " << arr1[i] << " discarded\n";
		}
		a1 = rand() % 15;

   // if a1 belongs to 0 to 3 then
   //     all ack after this (incl this one) lost
   // else
   //     all recieved

		if (a1 >= 0 && a1 <= fr_send_at_instance)
		{
			cout << "(Acknowledgement " << arr1[a1] << " & all after this lost)\n";
			sw = arr1[a1];
		}
		else
			sw = (sw + fr_send_at_instance) % wind;
	}
	else
	{
		f1 = rand() % fr_send_at_instance;

   // f1 gives index of the frame being lost

		for (int i = 0 ; i < f1 ; i++)
		{
			if (rw == arr1[i])
			{
				cout << " RECIEVER : Frame " << arr1[i] << " recieved correctly\n";
				rw = (rw + 1) % wind;
			}
			else
				cout << " RECIEVER : Duplicate frame " << arr1[i] << " discarded\n";
		}
		int ld = rand() % 2;
	// ld == 0 frame damaged
	// else frame lost
		if (ld == 0)
			cout << " RECIEVER : Frame " << arr1[f1] << " damaged\n";
		else
			cout << "            (Frame " << arr1[f1] << " lost)\n";

		for (int i = f1 + 1 ; i < fr_send_at_instance ; i++)
			cout << " RECIEVER : Frame " << arr1[i] << " discarded\n";

		cout << " (SENDER TIMEOUTS --> RESEND THE FRAME)\n";

		sw = arr1[f1];
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
 //clrscr();
 sender();
 getch();
}
