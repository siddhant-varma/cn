#include <iostream>
#include <cstdlib>

using namespace std;

string divide(string, string);
string change_data(string);

int main(void){
	string data, gdata, tdata;
	
	//Entering generator function
	cout<<"Enter G(x): ";
	cin>>gdata;
	
	//Entering Data Stream
	cout<<"Enter Data: ";
	cin>>data;
	
	//appends data stream with required no of zeros at the end
	for(int i = 0;i < gdata.length() - 1; i++){
		data += '0';
	}		
	cout<<"\nData stream after appending 0's :\t"<<data;
	
	//Replaces the placeholder bits with remainder bits
	data.replace(data.length() - gdata.length() + 1, gdata.length() - 1, divide(gdata, data));
	cout<<"\nT(x) is: \t"<<data;	//Transmitted bit stream
		
	tdata = divide(gdata, change_data(data));
	cout<<"\nRemainder for T(x):\t"<<tdata;
	
	return 0;
}

string divide(string divisor, string divident){
	
	int sizedvs = divisor.length();		//Size of divisor 
	int sizedvd = divident.length();	//Size of divident

	//Actual Division takes place here, with i as the iterator for sliding divison window
	//And j iterates in the sliding window
	for(int i = 0; i < sizedvd - sizedvs + 1; i++){
		if(divident[i] == '0'){
			for(int j = 0; j < sizedvs; j++){
				if(divident[i + j] == '0'){
					divident.replace(i + j, 1, "0");
				}
				else
					divident.replace(i + j, 1, "1");
			}
		}
		else{
			for(int j = 0; j < sizedvs; j++){
				
				if(divident[i + j] == divisor[j])
					divident.replace(i + j, 1, "0");
				else
					divident.replace(i + j, 1, "1");
			}
		}
	}
	
	//Remainder bit getting extracted and stored in temporary variable
	string temp = "";	//Temporary string for storing remainder bits
	for(int j = 0; j <  sizedvs - 1; j++)
		temp += divident[sizedvd - sizedvs + 1 + j];
		
	return temp;	//Returning remainder string
}

string change_data(string sent){
	int ch, pos;
	cout<<"\n\nEnter \t1)To Change a specific bit\n\t2)To Change a random bit\n\t3)Do not change data\t\t:";
	cin>>ch;
	switch(ch){
		case 1:
			cout<<"\nEnter Position you wish to change(Natural indexing):\t";
			cin>>pos;
			pos--;
			break;
		case 2:
			pos = rand() % sent.length();
			//cout<<"\n rand ="<<rand();
			cout<<"\n\t\tBit at "<<pos + 1<<" is being changed...\n";
			break;
		case 3:
			pos = -1;
			break;
	}
	if(pos>-1){
		char tbit = sent.at(pos);
		//cout<<"\n\ttarget bit is "<<tbit;
		if(tbit == '0')
			sent.replace(pos, 1, "1");
		else
			sent.replace(pos, 1, "0");
	}
	else{
		cout<<"\n\t\tUnchanged is being sent...\n";
	}
	cout<<"\nSent data is:\t"<<sent;
	
	return sent;
}

