/*
 * =====================================================================================
 *
 *       Filename:  const01.cxx
 *
 *    Description:  study first const method
 *
 *        Version:  1.0
 *        Created:  02/12/2014 11:05:50 AM
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
	int kmtemp = 10;
	const int kM = kmtemp;
	int b[kM];
	for(int i=0;i<10;i++)
	scanf("%d,",&b[i]);
	for(int k=0;k<10;k++)
	printf("%d, ",b[k]);
	return 0;
}
