#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

struct codeword{
	string msg, cw;
	int redundant_bits, parity;
	int **trutht;
	
	codeword(void){
		cw = "";
		redundant_bits = 1;
	}
};

codeword change_data(codeword);
int detect_error(codeword&);

int main (void){
	codeword data;
	cout<<"Enter Binary Data: ";
	cin>>data.msg;
	
	int m = data.msg.length();
	
	//Finding value of redundant_bits.
	for(int i = 1; i <= m + 1; i++)
		if( pow(2,i) >= (m+i+1) ){
			data.redundant_bits = i;
			break;
		}
	//cout<<data.redundant_bits<<endl;
	
	int size = data.redundant_bits + m + 1;
	int letter = 65;	//	char A ascii value
	int j = 0;			// 	Increment variable for codeword
	int t=(int) pow(2,data.redundant_bits);
	//cout<<"\nt = "<<t;
	for(int i = 1; i <= size; i++){	//	NOTE:	Iteration should be from 1 to size (inclusive)
		//cout<<"\ni = "<<i;
		if(t % i == 0)
			data.cw += letter++;	// Stuffing alphabets into codeword at 2^i places
		else
			data.cw += data.msg[j++];	// else usual codeword
	}
	cout<<data.cw;
	
	//2D Dynamic array for truth table.
	data.trutht = new int*[size];
	for(int k=0; k<size; k++)
		data.trutht[k] = new int[data.redundant_bits];
		
	cout<<"\nsize = "<<size;
	cout<<"\nr = "<<data.redundant_bits<<endl;
	
	//Generating Truth table for data.redundant_bits columns
	// Columns:	2^0		2^1		2^2		2^3	...
	for(int j=0;j < data.redundant_bits; j++){	//	Outer loop for row
		int counter = 0;						//	Keeps track of no of 0 or 1
		int turn = 0;							//  determines turn for 0 or 1 to be inputted into table
		for(int i=0;i < size; i++){				//	Inner loop for column
			if(counter < pow(2,j) && turn == 0)
				data.trutht[i][j] = 0;
			
			else if(counter < pow(2,j) && turn == 1)
				data.trutht[i][j] = 1;
			
			counter++;
			if(counter == pow(2,j)){			// If counter is 2^j, reset counter and invert turn.
				turn = !turn;
				counter = 0;
			}
		}		
	}
	/*
	//Displauing the Truth Table in correct format
	for(int i=0;i < size; i++){
		cout<<"i="<<i<<"\t\t";
		for(int j=0;j < data.redundant_bits; j++){
			cout<<trutht[i][data.redundant_bits-j-1];
		}
		cout<<endl;
	}
*/	
	//Counting Parity according to the Truth table occurence of 1 in respective places.
	for(int j = 0; j < data.redundant_bits; j++){
		int count1 = 0;
		for(int i = 1; i < size; i++){
			if (data.trutht[i][j] == 1 && data.cw[i-1] == '1'){
				//cout<<"\ti = "<<i;
				count1++;	
			}		
		}
		//cout<<"\nCount = "<<count1<<endl;
		if (count1 % 2)
			data.cw.replace(pow(2,j) - 1,1, "1");
		else
			data.cw.replace(pow(2,j) - 1,1, "0");
	}
	cout<<endl<<data.cw;
	codeword send = change_data(data);
	int pos = detect_error(send);
	cout<<"\nError occured at "<<pos;
	
	return 0;
}

codeword change_data(codeword sent){
	int ch, pos;
	cout<<"\nEnter \t1)To Change a specific bit\n\t2)To Change a random bit\n\t3)Do not change data\t\t:";
	cin>>ch;
	switch(ch){
		case 1:
			cout<<"\nEnter Position you wish to change(Natural indexing):\t";
			cin>>pos;
			pos--;
			break;
		case 2:
			pos = rand() % sent.cw.length();
			//cout<<"\n rand ="<<rand();
			cout<<"\n\t\tBit at "<<pos + 1<<" is being changed...\n";
			break;
		case 3:
			pos = -1;
			break;
	}
	if(pos>-1){
		char tbit = sent.cw.at(pos);
		//cout<<"\n\ttarget bit is "<<tbit;
		if(tbit == '0')
			sent.cw.replace(pos, 1, "1");
		else
			sent.cw.replace(pos, 1, "0");
	}
	else{
		cout<<"\n\t\tUnchanged is being sent...\n";
	}
	cout<<"\nSent data is "<<sent.cw;
	
	return sent;
}


int detect_error(codeword &received){
	int *check_bits = new int(received.redundant_bits);
	for(int j = 0; j < received.redundant_bits; j++){
		int count1 = 0;
		//cout<<endl;
		for(int i = 1; i < received.redundant_bits + received.msg.length() + 1; i++){
			if (received.trutht[i][j] == 1 && received.cw[i-1] == '1'){
				//cout<<"\ti = "<<i;
				count1++;	
			}	
		}
		//cout<<"\nCount = "<<count1;
		if (count1 % 2)
			check_bits[j] = 1;
		else
			check_bits[j] = 0;
			
		//cout<<endl<<check_bits[j];
	}
	string error = "";
	for(int k = 0; k < (received.redundant_bits); k++){
		//int index = received.redundant_bits - k - 1;
		//cout<<"\n\tbit is "<<check_bits[index]<<" and index is "<<index;
		error += to_string(check_bits[received.redundant_bits - k - 1]);
		//cout<<endl<<error;
	}
	
	cout<<"\nError Bit = "<<error;
	int target = stoi(error, nullptr, 2);
	return target;
	
}
