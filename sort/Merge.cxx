#include<iostream>
#include<iomanip>

using namespace std;

//#只完成兩段之間歸併的功能#%
void Merge(int a[], int b[], int low, int mid, int high);
void MergePass(int a[], int b[], int seg, int size);
void MergeSort(int a[], int size);

int main()
{
//	int a[] = {3, 5, 3, 6, 4, 7, 5, 7, 4};
	int a[] = {50, 10, 90, 30, 70, 40, 80, 60, 20};
	cout<<"size of a[]: "<<sizeof(a)<<endl;
	cout<<"size of one of a[]: "<<sizeof(*a)<<endl;
	cout<<"size of one of int: "<<sizeof(int)<<endl;
	MergeSort(a, sizeof(a) / sizeof(*a));
	//#輸出#%
	for(int i = 0; i < sizeof(a) / sizeof(*a); i++)
		cout << a[i] << ' ';
  cout << endl;
		
	return 0;
}
void Merge(int a[], int b[], int low, int mid, int high)
{
	int k = low;
	int begin1 = low;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = high;
	while(k <= high )
		{
			if(begin1 > end1)
				b[k++] = a[begin2++];
			else if(begin2 > end2)
				b[k++] = a[begin1++];
			else
				{
					if(a[begin1] <= a[begin2])
						b[k++] = a[begin1++];
					else
						b[k++] = a[begin2++];
				}
	  }
}

void MergePass(int a[], int b[], int seg, int size)
{
	int seg_start_ind = 0;
	while(seg_start_ind <= size - 2 * seg) //#size - 2 * seg的意思是滿足可兩兩歸併的最低臨界值#%
		{
			Merge(a, b, seg_start_ind, seg_start_ind + seg - 1, seg_start_ind + seg * 2 - 1);
			seg_start_ind += 2 * seg;
		}
	    //#如果一段是正好可歸併的數量而另一段則少於正好可歸併的數量#%
	if(seg_start_ind + seg < size)
		Merge(a, b, seg_start_ind, seg_start_ind + seg - 1, size - 1);
	else
		for(int j = seg_start_ind; j < size; j++) //#如果只剩下一段或者更少的數量#%
	    b[j] = a[j];
}

void MergeSort(int a[], int size)
{
	int* temp = new int[size];
	int seg = 1;
	while(seg < size)
		{
			MergePass(a, temp, seg, size);
			seg += seg;
			MergePass(temp, a, seg, size);
			seg += seg;
		}
	delete [] temp;
}

