#include "protocol.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int randNum(float chance){
	srand(0);
	int temp = rand();
	/*if(temp <= chance * 100){
		return temp;
	}
	else return 0;*/
	return temp;
}

