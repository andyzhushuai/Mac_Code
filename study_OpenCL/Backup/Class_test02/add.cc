#pragma OPENCL EXTENSION cl_amd_printf : enable
struct Complex 
{
   double rmz;
   double lmz;
};

//Get value. 
Complex getAComplex(double a,double b){ 
Complex Node=new Complex(); 
Node.rmz=a;
Node.lmz=b; 
return Node;} 

//Plus 
Complex addComplex(Complex complex1,Complex complex2) 
{ 
Complex Node=new Complex(); 
Node.rmz=complex1.rmz+complex2.rmz; 
Node.lmz=complex1.lmz+complex2.lmz; 
return Node; 
} 

//Minus 
Complex subComplex(Complex complex1,Complex complex2) 
{ 
Complex Node=new Complex(); 
Node.rmz=complex1.rmz-complex2.rmz; 
Node.lmz=complex1.lmz-complex2.lmz; 
return Node; 
} 

//Multiply 
Complex productComplex(Complex complex1,Complex complex2) 
{ 
Complex Node=new Complex(); 
Node.rmz=complex1.rmz*complex2.rmz-complex1.lmz*complex2.lmz; 
Node.lmz=complex1.lmz*complex2.rmz+complex2.lmz*complex2.rmz; 
return Node; 
} 
//Get Re of value 
double getComplexRmz(Complex complex1) 
{ 
return complex1.rmz; 
} 
//Get Im of value 
double getComplexLmz(Complex complex1) 
{ 
return complex1.lmz; 
}
__kernel void vecadd(__global const float* A, __global const float* B, __global float* C)
{
    struct Complex a, b;
    double x = 3, y = 4;
    a = getAComplex(x,y);
    b = getAComplex(y,x);
    printf("a = %f + (%f)*i", getComplexRmz(a), getComplexLmz(a));
    printf("b = %f + (%f)*i", getComplexRmz(b), getComplexLmz(b));

//    int abc = 100;
//    printf("Just a test!!!%d\n",abc);
//    double _Complex x;
//    double complex x = 5-5*I;
    int id = get_global_id(0);
    C[id] = A[id] + B[id];
}
