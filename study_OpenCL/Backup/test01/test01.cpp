#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#ifdef __APPLE__
    #include <OpenCL/cl.h>
		#include <OpenCL/cl_platform.h>
#elif defined(__linux__)
    #include <CL/cl.h>
		#include <CL/cl_platform.h>
#endif

#pragma comment (lib,"OpenCL.lib")

using namespace std;
#define NWITEMS 262144

//take a text to print out to string.
int convertToString(const char *filename, std::string& s)
{
  size_t size;
  char* str;
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
    return 0;
  }
  printf("Error: Failed to open file %s\n", filename);
  return 1;
}



int main(int argc, char* argv[])
{
  //create 3 Buffers in host memory.
  float *buf1 = 0;
  float *buf2 = 0;
  float *buf = 0;

  buf1 =(float *)malloc(NWITEMS * sizeof(float));
  buf2 =(float *)malloc(NWITEMS * sizeof(float));
  buf =(float *)malloc(NWITEMS * sizeof(float));
  
//initialize buf1, buf2 and buf.
  int i;
  srand( (unsigned)time( NULL ) );
  for(i = 0; i < NWITEMS; i++)
  buf1[i] = rand()%65535;
  srand( (unsigned)time( NULL ) +1000);
  for(i = 0; i < NWITEMS; i++)
  buf2[i] = rand()%65535;
  for(i = 0; i < NWITEMS; i++)
  buf[i] = buf1[i] + buf2[i];

  cl_uint status;

//create a platform
  cl_platform_id platform;                           							
  status = clGetPlatformIDs(0,&platform, NULL);

//obtain a OpenCL device
  cl_device_id device;											
  clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL); 

//create Context
  cl_context context = clCreateContext( NULL, 1, &device, NULL, NULL, NULL);				

//create Command queques
  cl_command_queue queue = clCreateCommandQueue( context, device, CL_QUEUE_PROFILING_ENABLE, NULL );    

//create 3 objects of OpenCL, and copy buf1 and buf2to clbuf1 and clbuf2 in secret.
  cl_mem clbuf1 = clCreateBuffer(context, 
				CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, 
				NWITEMS*sizeof(cl_float),buf1, 
				NULL );

  cl_mem clbuf2 = clCreateBuffer(context, 
				CL_MEM_READ_ONLY , 
				NWITEMS*sizeof(cl_float),NULL, 
				NULL );

  status = clEnqueueWriteBuffer(queue, clbuf2, 1, 0, NWITEMS*sizeof(cl_float), buf2, 0, 0, 0);

  cl_mem buffer = clCreateBuffer( context, 
				CL_MEM_WRITE_ONLY, 
				NWITEMS * sizeof(cl_float), 
				NULL, NULL );

  const char * filename = "vecadd.cl";
  std::string sourceStr;
  status = convertToString(filename, sourceStr);
  const char * source = sourceStr.c_str();
  size_t sourceSize[] = { strlen(source) };

//create object of program
  cl_program program = clCreateProgramWithSource( context, 1, &source, sourceSize, NULL);

//compile the object
  status = clBuildProgram( program, 1, &device, NULL, NULL, NULL );
  if(status != 0)
  {
    printf("clBuild failed:%d\n", status);
    char tbuf[0x10000];
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0x10000, tbuf,
    NULL);
    printf("\n%s\n", tbuf);
    return -1;
  }

// create Kernel object
  cl_kernel kernel = clCreateKernel( program, "cadd", NULL );
// set parameters of Kernel
  cl_int clnum = NWITEMS;
  clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*) &clbuf1);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*) &clbuf2);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*) &buffer);
// execute Kernel
  cl_event ev;
  size_t global_work_size = NWITEMS;
  clEnqueueNDRangeKernel( queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &ev);
  clFinish( queue );
// copy data back to host memory.
  cl_float *ptr;
  ptr = (cl_float *) clEnqueueMapBuffer( queue, buffer, CL_TRUE, CL_MAP_READ, 0, NWITEMS * sizeof(cl_float), 0, NULL, NULL, NULL );
// test results conpared with CPU
  if(!memcmp(buf, ptr, NWITEMS))
    printf("Verify passed\n");
  else 
    printf("verify failed");
  if(buf)
    free(buf);
  if(buf1)
    free(buf1);
  if(buf2)
    free(buf2);
//Release OpenCL objects
  clReleaseMemObject(clbuf1);
  clReleaseMemObject(clbuf2);
  clReleaseMemObject(buffer);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);
  return 0;
}
