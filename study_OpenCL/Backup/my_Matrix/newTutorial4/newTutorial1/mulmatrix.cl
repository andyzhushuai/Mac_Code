#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel void simpleMultiply( 
		__global float* c, int Wa, int Wb, 
		__global float* a, __global float* b)
 {

	//Get global position in Y direction
	int row = get_global_id(1);
	//Get global position in X direction
	int col   = get_global_id(0); 
	float sum = 0.0f; 
	//Calculate result of one element
	for (int i = 0; i < Wa; i++)
	 {
		sum += 
                     a[row*Wa+i] * b[i*Wb+col];
	}
	c[row*Wb+col] = sum;
}


