#include <iostream>

using namespace std;

int main(void){
	string address;
	cout<<"Enter IP Address:\t";
	cin>>address;
	
	string::size_type pos = 0, prev = -1, sz;
	int add[4];
	
	int i = 0;
	while(pos != string::npos){
		pos = address.find(".", prev+1);
		//cout<<"\tpos = "<<pos<<endl;
		string tar = address.substr(prev + 1, pos - prev - 1);
		//cout<<tar<<endl;
		prev = pos;
		add[i++] = stoi(tar, &sz);
	}
		
	/*pos = address.find(".");
	string tar = address.substr(0, address.find("."));
	cout<<tar;*/
	
	//int num = stoi(address.substr(0, address.find(".")), &pos);
	//cout<<num;
	bool valid = true;
	for(int j = 0; j < 4; j++){
		if(add[j] > 255 || add[j] < 0)
			valid = false;
	}
	
	if(valid){
		int num = add[0];
		if(num < 128)
			cout<<"\Class A";
		else if(num < 192)
			cout<<"\Class B";
		else if(num < 224)
			cout<<"\Class C";
		else if(num < 240)
			cout<<"\Class D";
		else
			cout<<"\Class E";
	}
	else
		cout<<"\nWrong IP Address...";
	
	/*
	switch(num){
		case :	
			break;
		case num < 192:	
			break;
		case num < 224:	cout<<"\Class C";
			break;
		case num < 240:	cout<<"\Class D";
			break;
		case num < 256:	cout<<"\Class E";
			break;
	}*/
	
}
