
//03.27.2013 P79 eg5-10

//author: Andy Zhu

# include <iostream>

using namespace std;

int main()
  {
    double x,y;
    char ch;
    cout <<"input x and y: " ;
    cin >>x >>y;
    cout <<"input ch: " ;
    cin >>ch;
    switch(ch)
      {
        case '+' : cout <<x <<"+" <<y <<" = " <<x+y <<endl;break;
        case '-' : cout <<x <<"-" <<y <<" = " <<x-y <<endl;break;
        case '*' : ;
        case '.' : cout <<x <<"*" <<y <<" = " <<x*y <<endl;break;
        case '/' : if (y==0.0) cout <<"error! " <<endl; //denominator is 0
                   else cout <<x <<"/" <<y <<" = " <<x/y <<endl;break;
        default: cout <<"Incorrect symbol!" <<endl;
      }
    return 0;
  }
