#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

struct codeword{
	string msg;
	string cw = "";
};

int main (void){
	codeword data;
	cout<<"Enter Binary Data: ";
	cin>>data.msg;
	
	int m = data.msg.length(), r = 0;
	
	//Finding value of r.
	for(int i = 1; i <= m + 1; i++)
		if( pow(2,i) >= (m+i+1) ){
			r = i;
			break;
		}
	//cout<<r<<endl;
	
	int size = r + m+1;
	int letter = 65;
	int j = 0;
	int t=(int) pow(2,r);
	//cout<<"\nt = "<<t;
	for(int i = 1; i <= size; i++){
		//cout<<"\ni = "<<i;
		if(t % i == 0)
			data.cw += letter++;
		else
			data.cw += data.msg[j++];
	}
	cout<<data.cw;
	
	//2D Dynamic array for truth table.
	int **trutht = new int*[size];
	for(int k=0; k<size; k++)
		trutht[k] = new int[r];
		
	//cout<<"\nsize = "<<size;
	//cout<<"\nr = "<<r<<endl;
	
	//Generating Truth table for r columns
	for(int j=0;j < r; j++){
		int counter = 0;
		int turn = 0;
		for(int i=0;i < size; i++){
			if(counter < pow(2,j) && turn == 0)
				trutht[i][j] = 0;
			
			else if(counter < pow(2,j) && turn == 1)
				trutht[i][j] = 1;
			
			counter++;
			if(counter == pow(2,j)){
				turn = !turn;
				counter = 0;
			}
		}		
	}
	/*
	//Displauing the Truth Table in correct format
	for(int i=0;i < size; i++){
		cout<<"i="<<i<<"\t\t";
		for(int j=0;j < r; j++){
			cout<<trutht[i][r-j-1];
		}
		cout<<endl;
	}
*/	
	//Counting Parity according to the Truth table occurence of 1 in respective places.
	for(int j = 0; j < r; j++){
		int count1 = 0;
		for(int i = 1; i < size; i++){
			if (trutht[i][j] == 1 && data.cw[i-1] == '1'){
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
	
	return 0;
}
