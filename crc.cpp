#include <iostream>
#include <cstdlib>

using namespace std;

int* divide(int*, int*, int, int);

int main(void){
	int *dx, *gx, dlen, glen;
	string data, gdata;
	
	//Entering generator function and converting it to array
	cout<<"\nEnter G(x): ";
	cin>>gdata;
	glen = gdata.length();
	gx = new int(glen);
	cout<<"\nG(x) is :\t";
	for(int i = 0;i < gdata.length(); i++){
		gx[i] = gdata[i] - '0';
		cout<<gx[i];
	}
	//cout<<"\n\t\tFine Here A";
	
	cout<<"\nEnter Data: ";
	cin>>data;
	
	//cout<<"\nGiven Data Stream:\t";
	dlen = data.length() + gdata.length() - 1; //	Size of transmitted bit stream
	dx = new int(dlen);
	
	//converts input data string to int array
	for(int i = 0;i < data.length(); i++){
		dx[i] = data[i] - '0';
		//cout<<dx[i];
	}
	//cout<<"\n\t\tFine Here B";
	
	//appends int array with req no of zeros at the end
	for(int i = 0;i < gdata.length() - 1; i++){
		dx[i + data.length()] = 0;
		//cout<<dx[i];
	}
	//cout<<"\n\t\tFine Here C";
		
	cout<<"\nData stream to be sent:\t";
	for(int i = 0;i < dlen; i++)
		cout<<dx[i];//<<"\t"<<i<<endl;
	
	
	cout<<"\nFine Here before tx";
	//int *tx = new int(dlen);
	cout<<"\nFine Here tx";
	//tx = divide(gx, dx);
	divide(gx, dx, glen, dlen);
	return 0;
}

int* divide(int* divisor, int* divident, int a, int b){
	int *rem, *tmp, *mult0, *sub;
	cout<<"\n\t\t\tFine Here divide()";
	int sizedvs = a;//sizeof(divisor)/sizeof(divisor[1]);
	int sizedvd = b;//sizeof(divident)/sizeof(divident[1]);
	cout<<"\n\tLength of divisor:\t"<<sizedvs;
	cout<<"\n\tLength of divident:\t"<<sizedvd;
	
	//rem = new int(sizedvs - 1);
	//tmp = new int(sizedvs);		//
	//mult0 = new int(sizedvs);	//Dynamic array of 0
	//sub = new int(sizedvs);		//To be XOR with tmp
	
	
	/*for(int i = 0; i < sizedvs - 1; i++){
		//tmp[i] = divident[i];
		mult0[i] = 0;
	}

	mult0[sizedvs - 1] = 0;*/
	
	//Actual Division takes place here
	for(int i = 0; i < sizedvd - sizedvs - 1; i++){
		
		//tmp[sizedvs - 1] = divident[i];
		//Resolving on the basis of 
		if(divident[i] == 0){
			//sub = mult0;
			for(int j = 0; j < sizedvs; j++){
				if(divident[i + j] == 0){
					divident[i + j] = 0;
				}
				else
					divident[i + j] = 1;
			}
		}
		else{
			for(int j = 0; j < sizedvs; j++){
				if(divident[i + j] == divisor[j]){
					divident[i + j] = 0;
				}
				else
					divident[i + j] = 1;
			}
			//sub = divisor;
		}
		
		
		/*
		for(int j = 0; j < sizedvs - 1; j++){
			tmp[j] = rem[j];	
		}*/
		
		cout<<endl;
		for(int j = 0; j <  sizedvs - 1; j++){
			cout<<divident[sizedvd - sizedvs + 1 + j];
	}
}
	return divident;
}
