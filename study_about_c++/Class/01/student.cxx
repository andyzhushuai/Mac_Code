#include "student.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Student::readdata()
{
	cout<<"Please input number: ";
	cin>>num;
	cout<<"Please input name: ";
	cin>>name;
	cout<<"Please input score: ";
	cin>>score;
	cout<<endl;
//	cin>>num>>name>>score;
	return;
}

void Student::writedata()
{
	cout<<setiosflags(ios::left);
	cout<<setw(6) <<num <<setw(10) <<name <<setw(8) <<score <<endl;
	return;
}
