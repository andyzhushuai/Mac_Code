all:
	g++ gclFile.cpp -c -L/usr/lib64 -lOpenCL -I/opt/AMDAPP/include -I/include
	g++ main.cpp -c -L/usr/lib64 -lOpenCL -I/opt/AMDAPP/include -I/include
	g++ gclFile.o  main.o -L/usr/lib64 -lOpenCL -o Fit
