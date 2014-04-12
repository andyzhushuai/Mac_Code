//#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel void cadd(__global const float *A, __global const float *B, __global float *C)
{
   int id = get_global_id(0);
   C[id] = A[id] + B[id];
   printf("successful!!!%f\n",C[id]);
//   printf("successful!!!\n");
}
