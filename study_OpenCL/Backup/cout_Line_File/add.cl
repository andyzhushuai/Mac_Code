#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel void vecadd(__global const float* A, __global const float* B, __global float* C)
{
    int id = get_global_id(0);
	double8 v;
//	v.s0 = 10;
//	v.s1 = 11;
//	v.s2 = 12;
//	v.s3 = 13;
//	v.s4 = 14;
//	v.s5 = 15;
//	v.s6 = 16;
//	v.s7 = 17;
//    printf("v: %f ",v.s0);
//    printf("   %f ",v.s1);
//    printf("   %f ",v.s2);
//    printf("   %f ",v.s3);
//    printf("   %f ",v.s4);
//    printf("   %f ",v.s5);
//    printf("   %f ",v.s6);
//    printf("   %f \n",v.s7);
//    printf("Just a test!!!\n%d\n",id);
//    printf(__FILE__);
//    printf("Just a test!!!\n%d\n",id);
//    printf("%d, %s\n",__LINE__,__FILE__);
    C[id] = A[id] + B[id];
}
