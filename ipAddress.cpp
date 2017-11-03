#include <iostream>

using namespace std;

int main(void){
	string address;
	cout<<"Enter IP Address:\t";
	cin>>address;
	
	string::size_type pos;
	
	//pos = address.find(".");
	//string tar = address.substr(0, address.find("."));
	//cout<<tar;
	
	int num = stoi(address.substr(0, address.find(".")), &pos);
	//cout<<num;
	
	if(num < 128)
		cout<<"\Class A";
	else if(num < 192)
		cout<<"\Class B";
	else if(num < 224)
		cout<<"\Class C";
	else if(num < 240)
		cout<<"\Class D";
	else if(num < 256)
		cout<<"\Class E";
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
