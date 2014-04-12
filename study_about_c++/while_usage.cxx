
// 03.27.2013 P84 eg5-12

// author: Andy Zhu

# include <iostream>

using namespace std;

int main()
  {
    int n;
    double sum;
    sum = 1.0, n = 1;
    while(n < 50)  
      {
        n = n+1; sum = sum+1/(double)n;
      }
    cout <<"sum = " <<sum <<endl;
    return 0;
}
