
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

struct node
{    
	int id;
	char name[20];
};

int one(void);
node two(node &a);
node three(node &a);
node four(node &a);

int main(void)
{
	one();
	cout<<"\n Back in Main()...";
	return 0;
}

int one()
{
	int ch;
	char c;
	node n,m;
	do
	{
		cout<<"Enter Node Id:";
		cin>>n.id;
		cout<<"Enter Node Name:";
		cin>>n.name;
		cout<<"\nEnter the function you want to send the message to:\n1.Two()\n2.Three()\n3.Four()\nEnter your choice:";
        cin>>ch;
        
        switch(ch)
        {
        	case 1:two(n);
				break;
            case 2:three(n);
				break;
            case 3:four(n);
				break;
            default:break;
		}
		
		cout<<"\nBack in One()\nEnter X to exit or Press any key to continue: ";
		cin>>c;
	}while(c!='x' and c!='X');
}

node two(node &a)
{
	cout<<"\nReceived by Two()\nNode id is:"<<a.id<<"\tNode name is "<<a.name;
	return a;
}

node three(node &a)
{
	cout<<"\nReceived by Three()\nNode id is:"<<a.id<<"\tNode name is "<<a.name;
	return a;
}

node four(node &a)
{
	cout<<"\nReceived by Four()\nNode id is:"<<a.id<<"\tNode name is "<<a.name;
	return a;
}



