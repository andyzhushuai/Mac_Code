#pragma OPENCL EXTENSION cl_amd_printf : enable
struct Complex 
{
   double rmz;
   double lmz;
};

//Get value. 
struct Complex getAComplex(double a,double b){ 
struct Complex Node; 
Node.rmz=a;
Node.lmz=b; 
return Node;} 

//Plus 
struct Complex PlusCom(struct Complex complex1, struct Complex complex2) 
{ 
struct Complex Node; 
Node.rmz=complex1.rmz+complex2.rmz; 
Node.lmz=complex1.lmz+complex2.lmz; 
return Node; 
} 

//Minus 
struct Complex MinuCom(struct Complex complex1, struct Complex complex2) 
{ 
struct Complex Node; 
Node.rmz=complex1.rmz-complex2.rmz; 
Node.lmz=complex1.lmz-complex2.lmz; 
return Node; 
} 

//Multiply 
struct Complex MultiCom(struct Complex complex1, struct Complex complex2) 
{ 
struct Complex Node; 
Node.rmz=complex1.rmz*complex2.rmz-complex1.lmz*complex2.lmz; 
Node.lmz=complex1.lmz*complex2.rmz+complex2.lmz*complex1.rmz; 
return Node; 
} 

//Divide
struct Complex DiviCom(struct Complex complex1,struct Complex complex2)
{
struct Complex Node;
Node.rmz=(complex1.rmz*complex2.rmz+complex1.lmz*complex2.lmz)/(complex2.rmz*complex2.rmz+complex2.lmz*complex2.lmz);
Node.lmz=(complex2.rmz*complex1.lmz-complex1.rmz*complex2.lmz)/(complex2.rmz*complex2.rmz+complex2.lmz*complex2.lmz);
return Node; 
}
//Get Re of value 
double getComplexRmz(struct Complex complex1) 
{ 
return complex1.rmz; 
} 

//Get Im of value 
double getComplexLmz(struct Complex complex1) 
{ 
return complex1.lmz; 
}

__kernel void vecadd(__global const float* A, __global const float* B, __global float* C)
{
    struct Complex a, b, c, d, e, f, g;
    double x = 3, y = 4;
    a = getAComplex(x,y);
    b = getAComplex(y,x);
    c = PlusCom(a, b);
    d = MinuCom(a, b);
    e = MultiCom(a, b);
    f = DiviCom(a, b);
    printf("a = %f + (%f)*i\n", getComplexRmz(a), getComplexLmz(a));
    printf("b = %f + (%f)*i\n", getComplexRmz(b), getComplexLmz(b));
    printf("Plus: c = %f + (%f)*i\n", getComplexRmz(c), getComplexLmz(c));
    printf("Minus: d = %f + (%f)*i\n", getComplexRmz(d), getComplexLmz(d));
    printf("Multiply: e = %f + (%f)*i\n", getComplexRmz(e), getComplexLmz(e));
    printf("Divide: f = %f + (%f)*i\n", getComplexRmz(f), getComplexLmz(f));
//    printf("a = %f + (%f)*i\n", a.rmz, a.lmz);
//    printf("b = %f + (%f)*i\n", b.rmz, b.lmz);

    int id = get_global_id(0);
    C[id] = A[id] + B[id];
}
