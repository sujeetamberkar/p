#include <stdio.h>
#include <OpenCL/opencl.h>
#include <stdlib.h>
# define MAX_SOURCE_SIZE 0x100000

int main(int argc, char const *argv[])
{
	// Create Input Array
	int LIST_SIZE;
	int i;
	printf("How Many Elements do you want to enter\t");
	scanf("%d",&LIST_SIZE);
	int * A = malloc(LIST_SIZE * sizeof(int))
	int * B = malloc(LIST_SIZE * sizeof(int))
	for (int i = 0;i<LIST_SIZE;i++)
	{
		A[i]=i;
	}
	for (int i = 0;i<LIST_SIZE;i++)
	{
		B[i]=i*10;
	}

	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("main.cl","r");
	if (!fp){
		fprintf(stderr, "Failed to load Kernel");
		getchar();
		exit(1);
	}

	source_str = (char *) malloc (MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);
	fclose(fp);

	// Get Platform Information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);

	// Create OpenCL Context
	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);
	
	// Create Command_Queue
	cl_command_queue command_queue = clCreateCommandQueue(context,device_id,0,&ret);

	// Create BUFFER_SIZE
	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,LIST_SIZE*sizeof(int),NULL,&ret);
	cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,LIST_SIZE*sizeof(int),NULL,&ret);
	cl_mem c_mem_obj =clCreateBuffer(context,CL_MEM_WRITE_ONLY,LIST_SIZE*sizeof(int),NULL,&ret);

	// Copy the list A in respective Buffer
	ret = clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(int),A,0,NULL,NULL);
	ret = clEnqueueWriteBuffer(command_queue,b_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(int),B,0,NULL,NULL);

	// Create Program from the kernel source
	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t *)&source_size,&ret);

	// Build a Program
	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	// Create the OpenCL Kernel Object 
	cl_kernel kernel = clCreateKernel(program,"vector_add",&ret);

	// Set Kernel Arguments 
	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);
	ret = clSetKernelArg(kernel,2,sizeof(cl_mem),(void*)&c_mem_obj);

	// Execute the OpenCL Kernel on Array
	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;
	// Execute the  Kernel on device 
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);
	ret = clFinish(command_queue);

	int *C = (int *) malloc(sizeof(int)*LIST_SIZE);
	ret = clEnqueueReadBuffer(command_queue,c_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(int),C,0,NULL,NULL);
	
	// Display the result to the screen 
	  for(i = 0; i <LIST_SIZE;i++)
	  {
	  	printf("%d+%d=%d\n",A[i],B[i],C[i]);
	  } 

	  // Clean Up 
	 ret =clFlush(command_queue);
	 ret = clReleaseKernel (kernel);
	 ret = clReleaseProgram(program);
	 ret =clReleaseMemObject(a_mem_obj);
	 ret = clReleaseMemObject(b_mem_obj);
	 ret = clReleaseMemObject(c_mem_obj);
	 ret = clReleaseCommandQueue(command_queue); 
	 ret = clReleaseContext(context);
	 free(A); 
	 free(B); 
	 free(C); 
	 getchar(); 
	return 0;
}

