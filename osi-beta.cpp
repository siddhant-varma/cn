#include<iostream>
#include<cstring>
#include<cstdio>
#include <bitset>
using namespace std;
string sep="%";
struct msg
{    
	string data;
};

int start(void);
msg input(msg &a);
int manip(string, msg &);
int bin(string);
msg application(msg &a);
msg presentation(msg &a);
msg session(msg &a);
msg transport(msg &a);
msg network(msg &a);
msg data_link(msg &a);
msg physical(msg &a);

//size_t index(string);
string header(msg &a);

string layer = {"Application", "Presesntation", "Session", "Transport", "Network", "Data Link", "Physical"};

int main(void)
{
	start();
	return 0;
}

int start(void)
{	
	msg m;
	input(m);
	application(m);
	cout<<"\nBack in Main()...";
	cout<<"\nCompiled Data: "<<m.data;
	cout<<"\nBinary Data: ";
	bin(m.data);
	header(m);
	return 0;
}

msg input(msg &m){	
	cout<<"Enter msg: ";
	cin>>m.data;
	return m;
}

msg application(msg &m){
	manip("Application",m);
	presentation(m);
	return m;
}

msg presentation(msg &m){
	manip("Presentation",m);
	session(m);
	return m;
}

msg session(msg &m){
	manip("Session",m);
	transport(m);
	return m;
}

msg transport(msg &m){
	manip("Transport",m);
	network(m);
	return m;
}


msg network(msg &m){
	manip("Session",m);
	data_link(m);
	return m;
}

msg data_link(msg &m){
	manip("Data Link",m);
	physical(m);
	return m;
}


msg physical(msg &m){
	manip("Physical",m);
	return m;
}

int manip(string layer, msg &m){
	string header;
	cout<<"\nEnter "<<layer<<" Header: ";
	cin>>header;
	m.data=header+sep+m.data;
	cout<<layer<<" Header Added...";
}

int bin(string s){
	for (std::size_t i = 0; i < s.size(); ++i)
 	 {
      cout << bitset<8>(s.c_str()[i]);
  	}
  	return 0;
}

/*size_t index(string s){
	size_t found = s.find(sep);
	return found;
}*/

string header(msg &s){
	string temp(s.data,0,s.data.find(sep));	
	cout<<endl<<temp;
	string left (s.data,2,s.data.length());
	s.data = left;
	cout<<endl<<"String after removing header:\t"<<s.data;
	return temp;
}
