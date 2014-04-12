__kernel void MatrixMul(__global const float *arr, __global const float *brr, __global float *crr, const int n)
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    for(int k = 0; k < n; ++k)
    {
        *crr += arr[k] * brr[k];
    }
}
