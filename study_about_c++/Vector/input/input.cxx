#include<iostream>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
	vector<int> facts;
//	facts.push_back(1);
//	facts.push_back(3);
//	facts.push_back(0);
//	sort(facts.begin(), facts.end());

	int num = 0;
	cout << "Please input a number: " << endl;
	cin>>num;
	int old_num = num;
	int tmp_num = 0;
	int width = 0;

	while(num>0)
	{
		facts.push_back(num%10);
		tmp_num = num - (num%10);
		num = tmp_num/10;
		width++;
	}

//	for(vector<int>::size_type i = 0; i < facts.size(); i++)
//		cout<<facts[i]<<" ";
//	cout<<endl;
//	cout<<"width: "<<width<<endl;

	sort(facts.begin(), facts.end());

//	for(vector<int>::size_type i = 0; i < facts.size(); i++)
//		cout<<facts[i]<<" ";
//	cout<<endl;

	int Max_Num = (facts[facts.size()-1] + 1) * pow(10,width-1);
//	cout<<"Max_Num: "<<Max_Num<<endl;
	vector<int> ifacts(width);
	int inum = 0;
	for(inum = old_num + 1; inum < Max_Num; inum++)
	{
		num = inum;
		tmp_num = 0;
		int i_bit = 0;
		while(num>0&&i_bit != width)
		{
			ifacts[i_bit] = num%10;
			tmp_num = num - (num%10);
			num = tmp_num/10;
			i_bit++ ;
		}
//		for(vector<int>::size_type i = 0; i < ifacts.size(); i++)
//			cout<<ifacts[i]<<" ";
//		cout<<endl;
		sort(ifacts.begin(), ifacts.end());
		if(facts == ifacts) 
		{
			cout<< " After " << old_num << ", Minimum is " << inum << endl;
			break;
		}
	}
	if(inum == Max_Num)
		cout<< old_num << " is the maxmum." << endl;

	return 0;
}
