/*
 * =====================================================================================
 *
 *       Filename:  const02.cxx
 *
 *    Description:  two consts to test
 *
 *        Version:  1.0
 *        Created:  02/12/2014 03:14:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhus (Suse), zhus@ihep.ac.cn
 *   Organization:  IHEP
 *
 * =====================================================================================
 */


#include <iostream>

using namespace std;

int main()
{
	int kmtemp = 10;
	const int kM = kmtemp + 1;
	int b[kM];
	for(int i=0;i<kM;i++)
//	scanf("%d,",&b[i]);
	cin>>b[i];
	for(int k=0;k<kM;k++)
//	printf("%d, ",b[k]);
	cout<<b[k];
	return 0;
}
