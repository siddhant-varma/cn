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
	
	cout<<"\nGiven Data Stream:\t";
	dlen = data.length() + gdata.length() - 1;
	dx = new int(dlen);
	
	//converts input data string to int array
	for(int i = 0;i < data.length(); i++){
		dx[i] = data[i] - '0';
		cout<<dx[i];
	}
	//cout<<"\n\t\tFine Here B";
	
	//appends int array with req no of zeros at the end
	for(int i = 0;i < gdata.length() - 1; i++){
		dx[i + data.length()] = 0;
		//cout<<dx[i];
	}
	//cout<<"\n\t\tFine Here C";
	
	cout<<"\nData stream to be sent:\t";
	for(int i = 0;i < data.length() + gdata.length() - 1; i++)
		cout<<dx[i];//<<"\t"<<i<<endl;
	
	tx = new int(dlen);
	tx = divide(gx, dx);
	
	return 0;
}

int* divide(int* divisor, int* divident){
	int *rem, *tmp, *mult0, *sub;
	
	int sizedvs = sizeof(divisor)/sizeof(divisor[1]);
	int sizedvd = sizeof(divident)/sizeof(divident[1]);
	
	
	rem = new int(sizedvs - 1);
	tmp = new int(sizedvs);		//
	mult0 = new int(sizedvs);	//Dynamic array of 0
	sub = new int(sizedvs);		//To be XOR with tmp
	
	//
	for(int i = 0; i < sizedvs - 1; i++){
		tmp[i] = divident[i];
		mult0[i] = 0;
	}

	mult0[sizedvs - 1] = 0;
	
	//Actual Division takes place here
	for(int i = sizedvs - 1; i < sizedvd; i++){
		
		tmp[sizedvs - 1] = divident[i];
		//Resolving on the basis of 
		if(tmp[0] == 0){
			sub = mult0;
		}
		else{
			sub = divisor;
		}
		
		for(int j = 1; j < sizedvs; j++){
			rem[j - 1] = tmp[j] ^ sub[j]; 
		}
		
		for(int j = 0; j < sizedvs - 1; j++){
			tmp[j] = rem[j];	
		}
		
		cout<<endl;
		for(int j = 0; j < sizedvs - 1; j++){
			cout<<rem[j];
	}
}
	return rem;
}
