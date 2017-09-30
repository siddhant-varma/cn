
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int one(void);
void two(string a);
void three(string a);
void four(string a);

int main(void)
{
	one();
	cout<<"\n Back in Main()...";
	return 0;
}

int one()
{
	int ch;
	string c;
	char a;
	do
	{
		cout<<"Enter Message:";
		cin>>c;
		cout<<"\nEnter the function you want to send the message to:\n1.Two()\n2.Three()\n3.Four()\nEnter your choice:";
        cin>>ch;
        
        switch(ch)
        {
        	case 1:two(c);
				break;
            case 2:three(c);
				break;
            case 3:four(c);
				break;
            default:break;
		}
		
		cout<<"\nBack in One()\nEnter X to exit or Press any key to continue: ";
		cin>>a;
	}while(a!='x' and a!='X');
}

void two(string a)
{
	cout<<"\nReceived by Two()\nMessage is "<<a;
	return;
}

void three(string a)
{
	cout<<"\nReceived by Three()\nMessage is "<<a;
	return;
}

void four(string a)
{
	cout<<"\nReceived by Four()\nMessage is "<<a;
	return;
}



