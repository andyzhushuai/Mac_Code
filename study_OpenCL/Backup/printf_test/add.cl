#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel void vecadd(__global const float* A, __global const float* B, __global float* C)
{
    int id = get_global_id(0);
    printf("Just a test!!!\n%d\n",id);
    C[id] = A[id] + B[id];
}
