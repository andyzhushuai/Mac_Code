// newTutorial1.cpp : Defines the entry point for the console application.
//

#include "targetver.h"
#include <tchar.h>
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;
#pragma comment (lib,"OpenCL.lib")

#define W 256


//把文本文件读入一个string中
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
			return NULL;
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
	float *src1=0;
	float *src2=0;
	float *outbuf=0;

	src1 = (float*)malloc(W*W*sizeof(float));
	src2 = (float*)malloc(W*W*sizeof(float));
	outbuf = (float*)malloc(W*W*sizeof(float));

	//初始化矩阵
	int i, j, k;
	srand( (unsigned)time( NULL ) ); 
	for(i = 0; i < W*W; i++)
		src1[i] = rand()%50;

	srand( (unsigned)time( NULL ) +1000);
	for(i = 0; i < W*W; i++)
		src2[i] = rand()%50;

	//cpu计算矩阵乘积
	for( i=0; i < W; i++)
	{
		for(j=0; j < W; j++)
		{
			outbuf[i*W + j] = 0;
			for(k=0; k < W; k++)
			{
				outbuf[i*W + j] += src1[i*W + k]*src2[k*W + j];
			}
		}
	}


	cl_uint status;
	cl_platform_id platform;

	//创建平台对象
	status = clGetPlatformIDs( 1, &platform, NULL );

	cl_device_id device;

	//创建GPU设备
	clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU,
		1,
		&device,
		NULL);
	//创建context
	cl_context context = clCreateContext( NULL,
		1,
		&device,
		NULL, NULL, NULL);
	//创建命令队列
	cl_command_queue queue = clCreateCommandQueue( context,
		device,
		CL_QUEUE_PROFILING_ENABLE, NULL );

	//创建三个OpenCL内存对象
	cl_mem clsrc1 = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		W*W*sizeof(cl_float),src1,
		NULL );
	cl_mem clsrc2 = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		W*W*sizeof(cl_float),src2,
		NULL );

	cl_mem cloutbuf = clCreateBuffer( context,
		CL_MEM_WRITE_ONLY,
		W*W * sizeof(cl_float),
		NULL, NULL );

	const char * filename  = "mulmatrix.cl";
	std::string  sourceStr;
	status = convertToString(filename, sourceStr);
	const char * source    = sourceStr.c_str();
	size_t sourceSize[]    = { strlen(source) };

	//创建程序对象
	cl_program program = clCreateProgramWithSource(
		context, 
		1, 
		&source,
		sourceSize,
		NULL);
	//编译程序对象
	status = clBuildProgram( program, 1, &device, NULL, NULL, NULL );
	if(status != 0)
	{
		printf("clBuild failed:%d\n", status);
		char tbuf[0x10000];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0x10000, tbuf, NULL);
		printf("\n%s\n", tbuf);
		return -1;
	}

	//创建Kernel对象
	cl_kernel kernel = clCreateKernel( program, "simpleMultiply", NULL );

	//设置Kernel参数
	cl_int dim = W;
	clSetKernelArg(kernel, 0, sizeof(cl_mem),  (void *)&cloutbuf); 
	clSetKernelArg(kernel, 1, sizeof(cl_int),  (void *)&dim);
	clSetKernelArg(kernel, 2, sizeof(cl_int),  (void *)&dim);
	clSetKernelArg(kernel, 3, sizeof(cl_mem),  (void *)&clsrc1);
	clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&clsrc2);


	//Set local and global workgroup sizes
	size_t localws[2] = {16,16} ; 
	size_t globalws[2] = {W, W};//Assume divisible by 16


	//执行kernel
	clEnqueueNDRangeKernel( 
		queue ,kernel, 
		2, 0, globalws, localws, 
		0, NULL, NULL);

	clFinish( queue );

	//数据拷回host内存
	// copy results from device back to host
	float *op_data=0;
	// op_data =(unsigned char *)malloc(mem_size);
	//status = clEnqueueReadBuffer(
	//	queue, d_op, 
	//	CL_TRUE,		//Blocking Read Back
	//	0, mem_size,(void*)op_data, NULL, NULL, NULL);
	op_data = (cl_float *) clEnqueueMapBuffer( queue,
		cloutbuf,
		CL_TRUE,
		CL_MAP_READ,
		0, 
		W*W*sizeof(cl_float),
		0, NULL, NULL, NULL );

	//验证GPU计算结果
	for(i = 0; i < W*W; i++)
	{
		if(abs(outbuf[i] - op_data[i]) > 0.0001)
		{
			printf("check failed\n");
			break;
		}
	}	
	if(i == W*W)
		printf("check passed\n");


	if(src1)
		free(src1);
	if(src2)
		free(src2);
	if(outbuf)
		free(outbuf);


	//删除OpenCL资源对象
	clReleaseMemObject(clsrc1); 
	clReleaseMemObject(clsrc2);
	clReleaseMemObject(cloutbuf);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	return 0;
}

