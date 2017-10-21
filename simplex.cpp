#include <iostream>
#include "protocol.h"

using namespace std;

int main(void){
	int i = 0;
	while(i < 10){
		int t = randNum(1.0);
		cout<<t<<endl;
		i++;
		/*WaitForEvent(Event e);
		if(event (RequestToSend)){
			GetData();
			MakeFrame();
			SendFrame();
		}*/
	}
}
