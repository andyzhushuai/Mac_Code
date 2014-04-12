#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel void vecadd(__global const float* A, __global const float* B, __global float* C)
{
    struct student
      {
         long int num;
	 char name[20];
	 char sex;
	 char addr[20];
      }a = {10101,"Zhu Shuai",'M',"123 Beijing Road"};
    printf("No: %ld\nname: %s\nsex: %c\naddress:%s\n", a.num, a.name, a.sex, a.addr);
//    int abc = 100;
//    printf("Just a test!!!%d\n",abc);
    complex  x;// = 5-5*I;
//    double _Complex x;
//    double complex x = 5-5*I;
    double xRe = creal(x);
    double xIm = cimag(x);
    printf("Complex x = %f + (%f)*i\n",xRe, xIm);
    int id = get_global_id(0);
    C[id] = A[id] + B[id];
}
