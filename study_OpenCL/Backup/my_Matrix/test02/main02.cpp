#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

#include<fstream>

#include <CL/cl.h>
#include <CL/cl_platform.h>

const int maxn = 4;

int convertToString(const char *filename, std::string& s)
{
    size_t size;
    char*  str;

    std::fstream f(filename, (std::fstream::in | std::fstream::binary));

    if(f.is_open())
    {
            size_t fileSize;
            f.seekg(0, std::fstream::end);
            size = fileSize = (size_t)f.tellg();
            f.seekg(0, std::fstream::beg);

            str = new char[size+1];
            if(!str)
            {
                    f.close();
                    return 0;
            }

            f.read(str, fileSize);
            f.close();
            str[size] = '\0';
    
            s = str;
            delete[] str;
            return 1;
        }
        printf("Error: Failed to open file %s\n", filename);
        return 0;
}

int main()
{
    float arr[] = { 1,  2,  3,  4,
            	    5,  6,  7,  8,
            	    9, 10, 11, 12,
            	   13, 14, 15, 16};
    float brr[] = { -1,  -2,  -3,  -4,
            	    -5,  -6,  -7,  -8,
                    -9, -10, -11, -12,
            	   -13, -14, -15, -16};

    float *crr = NULL;
    crr = (float*) malloc (maxn*maxn*sizeof(float));
    
    cl_uint numPlatforms;
        cl_platform_id platform = NULL;
    cl_int cnt = 0;
    cl_device_id device_id;

    cnt = clGetPlatformIDs(1, &platform, NULL);
    if (cnt != CL_SUCCESS) 
    {
        cout <<"something wrong getplatformIDs" << endl;
        return -1;
        }
    
    cnt = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
    if (cnt != CL_SUCCESS) 
    {
        cout <<"something wrong getdeviceIDs" << endl;
        return -1;
        }

    cl_context context = clCreateContext(0, 1, &device_id, NULL, NULL, &cnt);
    if (cnt != CL_SUCCESS) 
    {
        cout <<"something wrong context" << endl;
        return -1;
        }

    const char *filename = "MatrixMul.cl";
    string sourceStr;
    convertToString(filename,sourceStr);
    const char *source = sourceStr.c_str();
    //cout << source << endl;
    size_t sourceSize[] = {strlen(source)};

    cl_program program = clCreateProgramWithSource(context, 1, &source, sourceSize, &cnt);
    if (cnt != CL_SUCCESS) 
    {
        cout <<"something wrong program" << endl;
        return -1;
        }

    clBuildProgram(program, 1, &device_id, NULL, NULL, &cnt);
    if (cnt != CL_SUCCESS) 
    {
        cout <<"something wrong buildprogram" << endl;
        return -1;
        }

    cl_kernel kernel = clCreateKernel(program, "MatrixMul", &cnt);
    if (cnt != CL_SUCCESS) 
    {
        cout <<"something wrong with kernel" << endl;
        return -1;
        }

        cl_command_queue queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &cnt);
    if (cnt != CL_SUCCESS) 
    {
        cout <<"something wrong queue" << endl;
        return -1;
        }

    cl_mem a = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, maxn*maxn*sizeof(cl_float), arr, &cnt);
    cl_mem b = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, maxn*maxn*sizeof(cl_float), brr, &cnt);
    cl_mem c = clCreateBuffer(context, CL_MEM_READ_WRITE, maxn*maxn*sizeof(cl_float), NULL, &cnt);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*) & a);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*) & b);
    clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*) & c);
    clSetKernelArg(kernel, 3, sizeof(cl_int), (void*) & maxn);

    cl_event ev;
    size_t globalsz[2] = {maxn, maxn};
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, globalsz, NULL, 0, NULL, &ev);
    cnt = clFinish(queue);
    clWaitForEvents(1,&ev);

    clEnqueueReadBuffer(queue, c, CL_TRUE, 0, maxn*maxn*sizeof(cl_uint), crr, 0, NULL, NULL);

    for(int i = 0; i < maxn*maxn; ++i)
    {
        cout << crr[i] <<" ";
        if((i+1) % maxn == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
//    cout << "OK~"<<endl;
    clReleaseMemObject(a);
    clReleaseMemObject(b);
    clReleaseMemObject(c);
        clReleaseProgram(program);
        clReleaseCommandQueue(queue);
        clReleaseContext(context);

    system("pause");
    
    return 0;
}
