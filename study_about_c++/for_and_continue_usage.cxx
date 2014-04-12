
// 03.27.2013 P92 eg5-18

// author: Andy Zhu

# include <iostream>
# include <iomanip>

using namespace std;

int main()
  {
    int n;
    for (n = 100; n <= 200; n = n+1) 
    {
      if ((n%7 != 0) && (n%9 != 0)) continue;
      cout <<setw(5) <<n <<endl;
    }
    return 0; 
  }
