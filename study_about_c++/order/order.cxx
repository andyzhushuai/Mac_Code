/*
 * =====================================================================================
 *
 *       Filename:  order.cxx
 *
 *    Description:  test MaoPao order
 *
 *        Version:  1.0
 *        Created:  02/12/2014 10:45:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhus (Suse), zhus@ihep.ac.cn
 *   Organization:  IHEP
 *
 * =====================================================================================
 */

#include <stdio.h>
int main()
{
	const int kM = 10;
	int a[kM]={0};
//		for(int k=0;k<10;k++)
//		printf("%d, ",b[k]);
//	a[kM]={5,6,4,7,8,3,2,9,10,1};
	int i,j,k,n,temp;
	for(i=0;i<kM;i++)
		scanf("%d,",&a[i]);
//	for(i=0;i<kM-1;i++)
	for(i=0;i<3;i++)
	{
		for(j=0;j<kM-i-1;j++)
        if(a[j]<a[j+1])
		//if(a[j]>a[j+1])
		{
			temp = a[j];
			a[j] = a[j+1];
			a[j+1] = temp;
		}
//		for(k=0;k<10;k++)
		printf("%d, ",a[kM-1-i]);
		printf("\n");
	}
	return 0;
}
