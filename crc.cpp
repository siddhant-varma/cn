#include <iostream>
#include <cstdlib>

using namespace std;

void divide(int [], int [], int, int);

int main(void){
	int *dx, *gx, *tx, dlen, glen;
	string data, gdata, tdata;
	
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
		
	cout<<"\nData stream after appending 0's :\t";
	for(int i = 0;i < dlen; i++)
		cout<<dx[i];//<<"\t"<<i<<endl;
		
	//tdata = data;
	cout<<"\nData stream of tx :\t"<<data;
	
	cout<<"\nFine Here before tx";
	//int *tx = dx;
	cout<<"\nFine Here tx";
	//tx = divide(gx, dx, glen, dlen);
	divide(gx, dx, glen, dlen);
	
	cout<<"\n\t\t\tFine here back in main()\tT(x) is: \t"<<data;
	
	for(int i = 0;i < glen - 1; i++){
		int temp = dx[dlen - glen + 1];
		cout<<temp;
		//data += temp;//<<"\t"<<i<<endl;	
	}
	
	cout<<"\nData stream After conversion:\t";
	for(int i = 0;i < dlen; i++)
		cout<<dx[i];

	//cout<<"\nTransmitted stream of tx :\t"<<tdata;
		
	return 0;
}

void divide(int divisor[], int divident[], int a, int b){
	
	cout<<"\n\t\t\tFine Here divide()";
	
	int sizedvs = a;//sizeof(divisor)/sizeof(divisor[1]);
	int sizedvd = b;//sizeof(divident)/sizeof(divident[1]);
	
	//cout<<"\n\tLength of divisor:\t"<<sizedvs;
	//cout<<"\n\tLength of divident:\t"<<sizedvd;

	//Actual Division takes place here
	for(int i = 0; i < sizedvd - sizedvs + 1; i++){
		if(divident[i] == 0){
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
		}
		/*cout<<endl;
		for(int k = 0;k < sizedvd; k++)
			cout<<divident[k];*/
	}
	
	cout<<endl;
	for(int j = 0; j <  sizedvs - 1; j++){
		cout<<divident[sizedvd - sizedvs + 1 + j];
}
	//return divident;
}
