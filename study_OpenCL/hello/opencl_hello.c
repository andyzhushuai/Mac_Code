#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
    #include <OpenCL/cl.h>
#elif defined(__linux__)
    #include <CL/cl.h>
#endif

int main()
{
  cl_uint NumPlatforms;
  clGetPlatformIDs (0, NULL, &NumPlatforms);
    
  cl_platform_id PlatformIDs[NumPlatforms];
  clGetPlatformIDs(NumPlatforms, PlatformIDs, NULL);

  char platformName[64];
  size_t nameLen;
  cl_int res = clGetPlatformInfo(PlatformIDs[0], CL_PLATFORM_NAME, 64, platformName, &nameLen);
  if (res != CL_SUCCESS) 
	{
     fprintf(stderr, "Err: %d\n", res);
     exit(1);
  }   
   platformName[nameLen] = 0;

   char openclVersion[64];
   res = clGetPlatformInfo(NULL, CL_PLATFORM_VERSION, 64, openclVersion, &nameLen);
   if (res != CL_SUCCESS) 
	 {
     fprintf(stderr, "Err: %d\n", res);
     exit(1);
   }   
   openclVersion[nameLen] = 0;
   printf("hello, %s's %s\n", platformName, openclVersion);

   return 0;
}
