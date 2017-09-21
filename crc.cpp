#include <iostream>
#include <cstdlib>

using namespace std;

int* divide(int*, int*);

int main(void){
	int *dx, *gx, *tx, dlen;
	string data, gdata;
	
	cout<<"\nEnter G(x): ";
	cin>>gdata;
	gx = new int(gdata.length());
	for(int i = 0;i < gdata.length(); i++){
		gx[i] = gdata[i] - '0';
		cout<<gx[i];
	}
	//cout<<"\n\t\tFine Here A";
	
	cout<<"\nEnter Data: ";
	cin>>data;
	dlen = data.length() + gdata.length() - 1;
	dx = new int(dlen);
	for(int i = 0;i < data.length(); i++){
		dx[i] = data[i] - '0';
		cout<<dx[i];
	}
	//cout<<"\n\t\tFine Here B";
	cout<<endl;
	
	for(int i = 0;i < gdata.length() - 1; i++){
		dx[i + data.length()] = 0;
		//cout<<dx[i];
	}
	//cout<<"\n\t\tFine Here C";
	
	for(int i = 0;i < data.length() + gdata.length() - 1; i++){
		cout<<dx[i];//<<"\t"<<i<<endl;
	}
	
	tx = new int(dlen);
	
	
	return 0;
}

int* divide(int* divisor, int* divident){
	int* rem;
	
}
