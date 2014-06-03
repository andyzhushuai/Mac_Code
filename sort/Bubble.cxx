#include<iostream>
#include<iomanip>

using namespace std;
void bubbleSort(int a[], int size);

int main()
{
	int array[] = {34, 65, 12, 43, 67, 5, 78, 10, 3, 70}, k;
	int len = sizeof(array)/sizeof(int);
	cout<<setw(3)<<"The original array are: "<<endl;
	for(k=0; k<len; k++)
		cout<<setw(3)<<array[k]<<", ";
	cout<<setw(3)<<endl;
	cout<<setw(3)<<endl;
	bubbleSort(array, len);
	cout<<setw(3)<<"The sorted array are: "<<endl;
	for(k=0; k<len; k++)
		cout<<setw(3)<<array[k]<<", ";
	cout<<setw(3)<<endl;
	cout<<setw(3)<<endl;
//	system("pause");
	return 0;
}

void bubbleSort(int a[], int size)
{
	int temp;
	for(int pass=1; pass<size; pass++)
	{
		for(int k=0; k<size-pass; k++)
			if(a[k]>a[k+1])
			{
				temp = a[k];
				a[k] = a[k+1];
				a[k+1] = temp;
			}
		cout<<setw(3)<<"第"<<pass<<"轮排序后: ";
		for(int i=0; i<size; i++)
			cout<<setw(3)<<a[i]<<", ";
		cout<<setw(3)<<endl;
	}
}
