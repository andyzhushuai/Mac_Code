/*
   ???openCL?????
   ?????
   ???2012.11.20
*/
#include <iostream>
#include<time.h>
#include <string.h> 
#include<math.h>
#include <vector>
#include <CL/cl.h>
#include <fstream>
using namespace std;
//kernel??
std::string
convertToString(const char *filename)//?kernel?????????????????????
{
    size_t size;
    char*  str;
    std::string s;

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
            std::cout << "Memory allocation failed";
            return NULL;
        }

        f.read(str, fileSize);
        f.close();
        str[size] = '\0';
    
        s = str;
        delete[] str;
        return s;
    }
    else
    {
        std::cout << "\nFile containg the kernel code(\".cl\") not found. Please copy the required file in the folder containg the executable.\n";
        exit(1);
    }
    return NULL;
}

int main()
{
	double start,end,time1,time2;
	//????
	cl_int ciErrNum;
	cl_platform_id platform;
	ciErrNum = clGetPlatformIDs(1, &platform, NULL);
	if(ciErrNum != CL_SUCCESS)
	{
		cout<<"??????"<<endl;
		return 0;
	}
	//??????
	cl_device_id device;
	cl_int   status;
    cl_uint maxDims;
    cl_event events[2];
    size_t globalThreads[1];
    size_t localThreads[1];
    size_t maxWorkGroupSize;
    size_t maxWorkItemSizes[3];

    //////////////////////////////////////////////////////////////////// 
    // STEP 7 Analyzing proper workgroup size for the kernel
    //          by querying device information
    //    7.1 Device Info CL_DEVICE_MAX_WORK_GROUP_SIZE
    //    7.2 Device Info CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS
    //    7.3 Device Info CL_DEVICE_MAX_WORK_ITEM_SIZES
    //////////////////////////////////////////////////////////////////// 
    
    
    /**
    * Query device capabilities. Maximum 
    * work item dimensions and the maximmum
    * work item sizes
    */ 
	ciErrNum = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    status = clGetDeviceInfo(
        device, 
        CL_DEVICE_MAX_WORK_GROUP_SIZE, 
        sizeof(size_t), 
        (void*)&maxWorkGroupSize, 
        NULL);
    if(status != CL_SUCCESS) 
    {  
        std::cout << "Error: Getting Device Info. (clGetDeviceInfo)\n";
        return 0;
    }
    
    status = clGetDeviceInfo(
        device, 
        CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 
        sizeof(cl_uint), 
        (void*)&maxDims, 
        NULL);
    if(status != CL_SUCCESS) 
    {  
        std::cout << "Error: Getting Device Info. (clGetDeviceInfo)\n";
        return 0;
    }

    status = clGetDeviceInfo(
        device, 
        CL_DEVICE_MAX_WORK_ITEM_SIZES, 
        sizeof(size_t)*maxDims,
        (void*)maxWorkItemSizes,
        NULL);
    if(status != CL_SUCCESS) 
    {  
        std::cout << "Error: Getting Device Info. (clGetDeviceInfo)\n";
        return 0;
    }
	cout<<"maxWorkItemSizes"<<maxWorkItemSizes<<endl;
	cout<<"maxDims"<<maxDims<<endl;
	cout<<"maxWorkGroupSize"<<(int)maxWorkGroupSize<<endl;
	
	//?????
	cl_context_properties cps[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0};
	cl_context ctx = clCreateContext(cps, 1, &device, NULL, NULL, &ciErrNum);
	if(ciErrNum != CL_SUCCESS)
	{
		cout<<"???????"<<endl;
		return 0;
	}
	cl_command_queue myqueue = clCreateCommandQueue(ctx,device,0,&ciErrNum);
	if(ciErrNum != CL_SUCCESS)
	{
		cout<<"??????"<<endl;
		return 0;
	}
	//??buffer,????
	float *A = NULL; // ????
	float *B = NULL; // ????
	float *C = NULL; // ????

	int wA=20,hA=20;
	int wB=20,hB=20;
	int wC=20,hC=20;

	// ?????
	const int  elementsA = wA*hA;
	const int  elementsB = wB*hB;
	const int  elementsC = hA*wB;
	
	// ??????
	size_t datasizeA = sizeof(float)*elementsA;
	size_t datasizeB = sizeof(float)*elementsB;
	size_t datasizeC = sizeof(float)*elementsC;
	// ??????
	A = (float*)malloc(datasizeA);
	B = (float*)malloc(datasizeB);
	C = (float*)malloc(datasizeC);

	// ???????
	for(int i = 0;i < elementsA;i++)
	{
		//A[i] = std::rand()/1.5;
		A[i] = rand()/1.5;
		//B[i] = std::rand()/1.5;
	}
	for(int i = 0;i < elementsB;i++)
	{
		//B[i] = std::rand()/1.5;
		B[i] = rand()/1.5;
		//B[i] = std::rand()/1.5;
	}
	

	cl_mem bufferA = clCreateBuffer(ctx,CL_MEM_READ_ONLY,wA*hA*sizeof(float),NULL,&ciErrNum);
	ciErrNum = clEnqueueWriteBuffer(myqueue,bufferA,CL_TRUE,0,wA*hA*sizeof(float),(void*)A,0,NULL,NULL);

	cl_mem bufferB = clCreateBuffer(ctx,CL_MEM_READ_ONLY,wB*hB*sizeof(float),NULL,&ciErrNum);
	ciErrNum = clEnqueueWriteBuffer(myqueue,bufferB,CL_TRUE,0,wB*hB*sizeof(float),(void*)B,0,NULL,NULL);

	cl_mem bufferC = clCreateBuffer(ctx,CL_MEM_WRITE_ONLY,hA*wB*sizeof(float),NULL,&ciErrNum);

	//???kernel??
	const char * filename  = "simpleMultiply.cl";
    std::string  sourceStr = convertToString(filename);
    const char * source    = sourceStr.c_str();
    size_t sourceSize[]    = { strlen(source) };
	//???CL???????
    cl_program myprog = clCreateProgramWithSource(
                  ctx, 
                  1, 
                  &source,
                  sourceSize,
                  &ciErrNum);
	//cl_program myprog = clCreateProgramWithSource(ctx,1,(const char**)&programSource,NULL,&ciErrNum);
	ciErrNum = clBuildProgram(myprog,0,NULL,NULL,NULL,NULL);

	cl_kernel mykernel = clCreateKernel(myprog,"simpleMultiply",&ciErrNum);
	//????
	clSetKernelArg(mykernel,0,sizeof(cl_mem),(void*)&bufferC);
	clSetKernelArg(mykernel,1,sizeof(cl_mem),(void*)&wA);
	clSetKernelArg(mykernel,2,sizeof(cl_mem),(void*)&hA);
	clSetKernelArg(mykernel,3,sizeof(cl_mem),(void*)&wB);
	clSetKernelArg(mykernel,4,sizeof(cl_mem),(void*)&hB);
	clSetKernelArg(mykernel,5,sizeof(cl_mem),(void*)&bufferA);
	clSetKernelArg(mykernel,6,sizeof(cl_mem),(void*)&bufferB);

	size_t localws[2] ={20,20};
	size_t globalws[2]={wC,hC};
	//
	//
	start = clock();
	ciErrNum = clEnqueueNDRangeKernel(myqueue,mykernel,2,NULL,globalws,localws,0,NULL,&events[0]);
	//????
	status = clWaitForEvents(1, &events[0]);
    if(status != CL_SUCCESS) 
    { 
        std::cout <<
            "Error: Waiting for kernel run to finish. \
            (clWaitForEvents)\n";
        return 0;
    }

    status = clReleaseEvent(events[0]);
	//?????????
	end = clock();
	time1=end-start;
	cout<<"shijian "<<time1<<endl;
	ciErrNum = clEnqueueReadBuffer(myqueue,bufferC,CL_TRUE,0,wC*hC*sizeof(float),(void*)C,0,NULL,&events[1]);
	
	status = clWaitForEvents(1, &events[1]);
    if(status != CL_SUCCESS) 
    { 
        std::cout <<
            "Error: Waiting for read buffer call to finish. \
            (clWaitForEvents)\n";
        return 0;
    }
    
    status = clReleaseEvent(events[1]);
    if(status != CL_SUCCESS) 
    { 
        std::cout <<
            "Error: Release event object. \
            (clReleaseEvent)\n";
        return 0;
    }
	//
	return 0;
}
