
//03.27.2013 P36 example

//author: Andy Zhu

# include <iostream>

using namespace std;

int main()
  {
    const int x = 35;
    const double pi = 3.1415726;
//  const int x;                                                        //error! forgot giving"x" the value
//  pi = 3.14;                                                          //error! mustn't change const variable
    const int y = 6, z = y+3;
//  cout <<"x = " <<x <<endl;
//  cout <<"pi = " <<pi <<endl;
//  cout <<"y = " <<y <<endl;
//  cout <<"z = " <<z <<endl; 
  }
