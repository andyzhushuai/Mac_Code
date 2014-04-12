#include<iostream>

using namespace std;

void calEva(int *a, int& sum);
void calEva(int *a);

int main()
{
   int a[10];
   int sum = 0;
   void calEva(int *a, int& sum);
   void calEva(int *a);
   cout<<"Sum = "<<sum<<endl;
   
   return 0;
}

void calEva(int a[], int& sum)
{
   for(int i=0;i<10;i++)
   {
      a[i] = i;
      cout<<"a["<<i<<"] = "<<a[i]<<endl;
      sum = sum + a[i];
   }
}

void calEva(int a[])
{
   for(int i=0;i<10;i++)
   {
      a[i] = i;
      cout<<"a["<<i<<"] = "<<a[i]<<endl;
   }
}
