#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel void vecadd(__global const float* A, __global const float* B, __global float* C, bool Sig)
{
    int abc = 100;
    if (Sig == true)printf("Just a test!!!%d\n",abc);
//    complex  x;// = 5-5*I;
//    double _Complex x;
//    double complex x = 5-5*I;
//    double xRe = creal(x);
//    double xIm = cimag(x);
//    printf("Complex x = %f + (%f)*i\n",xRe, xIm);
    int id = get_global_id(0);
    C[id] = A[id] + B[id];
}
