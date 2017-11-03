#include <iostream>

using namespace std;

int main(void){
	string address;
	cout<<"Enter IP Address:\t";
	cin>>address;
	
	string::size_type pos;
	
	int num = stoi(address.substr(0, address.find(".")), &pos);
	
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
	
}
