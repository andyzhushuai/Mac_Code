#pragma OPENCL EXTENSION cl_amd_printf : enable
    struct student
      {
         double Re;
         double Im;
      };
__kernel void vecadd(__global const float* A, __global const float* B, __global float* C)
{   struct student a = {3,4}, b = {4,3};
//    printf("Re = %f, Im = %f\n", a.Re, a.Im);
//    int abc = 100;
      double xxx = 100;
      double yyy = sqrt(xxx);
      printf("yyy = %f\n",yyy);
//    printf("Just a test!!!%d\n",abc);
//    complex  x;// = 5-5*I;
//    double _Complex x;
//    double complex x = 5-5*I;
//    double xRe = creal(x);
//    double xIm = cimag(x);
//    printf("Complex x = %f + (%f)*i\n",xRe, xIm);
    int id = get_global_id(0);
    C[id] = A[id] + B[id];
}
