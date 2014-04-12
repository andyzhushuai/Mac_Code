
// 03.27.2013 P86 eg5-12

// author: Andy Zhu

# include <iostream>

using namespace std;

int main()
  {
    int n;
    double sum;
    sum = 1.0, n = 1;
    do
      {
        n = n+1; sum = sum+1/(double)n;
      }
    while(n < 50) ;
    cout <<"sum = " <<sum <<endl;
    return 0;
  }
