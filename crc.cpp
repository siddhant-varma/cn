#include <iostream>
#include <cstdlib>

using namespace std;

string divide(string, string);

int main(void){
	string data, gdata, rx;
	
	//Entering generator function and converting it to array
	cout<<"\nEnter G(x): ";
	cin>>gdata;
	
	cout<<"\nEnter Data: ";
	cin>>data;
	
	//cout<<"\nGiven Data Stream:\t";

	cout<<"\n\t\tFine Here B";
	
	//appends int array with req no of zeros at the end
	for(int i = 0;i < gdata.length() - 1; i++){
		data += '0';
	}
	//cout<<"\n\t\tFine Here C";
		
	cout<<"\nData stream after appending 0's :\t"<<data;
	
	rx = divide(gdata, data);
	data.replace(data.length() - gdata.length() + 1, gdata.length() - 1, rx);
	cout<<"\n\t\t\tFine here back in main()\tT(x) is: \t"<<data;
		
	return 0;
}

string divide(string divisor, string divident){
	
	cout<<"\n\t\t\tFine Here divide()";
	
	int sizedvs = divisor.length();
	int sizedvd = divident.length();
	
	//cout<<"\n\tLength of divisor:\t"<<sizedvs;
	//cout<<"\n\tLength of divident:\t"<<sizedvd;

	//Actual Division takes place here
	for(int i = 0; i < sizedvd - sizedvs + 1; i++){
		if(divident[i] == '0'){
			for(int j = 0; j < sizedvs; j++){
				if(divident[i + j] == '0'){
					divident.replace(i + j, 1, "0");//divident[i + j] = 0;
				}
				else
					divident.replace(i + j, 1, "1");//divident[i + j] = 1;
			}
		}
		else{
			for(int j = 0; j < sizedvs; j++){
				if(divident[i + j] == divisor[j]){
					divident.replace(i + j, 1, "0");//divident[i + j] = 0;
				}
				else
					divident.replace(i + j, 1, "1");//divident[i + j] = 1;
			}
		}
	}
	
	cout<<endl<<"Fine after actual division..\n"<<divident<<endl;
	string temp = "";
	for(int j = 0; j <  sizedvs - 1; j++){
		cout<<divident[sizedvd - sizedvs + 1 + j];
		temp += divident[sizedvd - sizedvs + 1 + j];
}
	return temp;
}
