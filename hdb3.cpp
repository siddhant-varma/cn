#include <iostream>
#include <cstring>
using namespace std;

const int HIGH = 1;
const int NEUTRAL = 0;
const int LOW = -1;

struct data{
	string inp;
	string out;
};

int main(void){
	data a;
	int ch, l = -1, count = 0, countnz = 0;
	string temp0;
	
	
	cout<<"Enter Data Signal: ";
	cin>>a.inp;
	
	cout<<"\nTo enter last polarity of signal Press \n\t1) HIGH\n\t2) LOW\n\t";
	cin>>ch;
	
	switch(ch){
		case 1: l = HIGH;
		break;
		
		case 2: l = LOW;
		break;
		
		default: cout<<"\n\t\t\tWrong Choice Entered...Setting last polarity to LOW...";
		l = LOW;
		break;
	}
	
	for(int i=0;i<a.inp.length(); i++){
		switch(a.inp[i]){
			case '1': switch(l){
					case HIGH: a.out += 'N'; // N refers to as Negative
							l = LOW;
							break;
					
					case LOW: a.out += '1';
							l = HIGH;
							break;
			}
			countnz += 1;
			count = 0;
			break;
			
			case '0': 
			count += 1;
			a.out += '0';
			if (count > 3){
				switch( countnz % 2){
					case 0:		//Even
							if (l == HIGH){
									a.out.replace(i - 3, 1, "N");
									a.out.replace(i, 1, "N");
									l = LOW;
								}
								
								else{
									a.out.replace(i - 3, 1, "1");
									a.out.replace(i, 1, "1");
									l = HIGH;
								}
								break;
					
					
					case 1: 		//Odd
								if (l == HIGH){
									a.out.replace(i, 1, "1");
									l = HIGH;
								}
								
								else{
									a.out.replace(i, 1, "N");
									l = LOW;
								}
								
								break;
			}
			count = 0;
			countnz = 0;
		}
		break;	
		}
	}
	
	cout<<"\n\tHDB3 Scrambling::\n\tHere N represens Negative value(Below Avg. Line)-";

	cout<<"\n\n\tInput Binary Data: \t\t"<<a.inp;
	cout<<"\n\tOutput Data Signal Values: \t"<<a.out;
	
	return 0;
}