#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooArgSet.h"
#include "TSystem.h"
#include "RooCategory.h"
#include "RooSimultaneous.h"
#include "RooFitResult.h"
#include "TTree.h"
#include "RooArgList.h"
#include "RooPrintable.h"
#include "RooMinuit.h"
#include "RooAddPdf.h"
#include "RooArgusBG.h"
#include "RooConstVar.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "RooNLLVar.h"
#include <string.h>
#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <TStopwatch.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "DPFCoord.hh"
#include "DPFAngular.hh"
#include "DPFPropogator.hh"
//#include "PWAPdfpi.hh"
//#include "PWAPdfka.hh"
#include "PWAPdf.hh"
#include "DPFPWAPoint.hh"
#include "DPFNLLVar.hh"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <CL/cl_platform.h>
//#define BILLION 1E9
using namespace RooFit ;
using namespace std;
void convertToString(const char*, std::string&);
int main()
{

//   const TString& datName01 ="sig_in_sig.dat";
   Int_t Nphsmc = 500000;

   TString  outName= "try.C";
   bool USEGPU = true;//if use GPU to calculate Integral.
   DPFNLLVar::USEGPU = USEGPU;
//   Int_t    NSegments    = 1000;//?
//   Int_t    Nresolution  =  101;//?
   cl_uint status;				//same
   cl_int err;					//same
   cl_platform_id platform;
   status = clGetPlatformIDs (1, &platform, NULL);
   cl_device_id device;
   clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU,
             1,
             &device,
             NULL);
   cl_context context = clCreateContext( NULL,
             1,
             &device,
             NULL, NULL, NULL);
   PWASingNLL::setContext(context);
   cl_command_queue queue = clCreateCommandQueue( context,
             device,
             CL_QUEUE_PROFILING_ENABLE, NULL );
   PWASingNLL::setQueue(queue);
   const char * filename = "calEva_Kernel.cl";
//   const char * filename = "test.cl";
   std::string sourceStr;
   convertToString(filename, sourceStr);
   const char * source = sourceStr.c_str();                      //???
   size_t sourceSize[] = { strlen(source) };
   cl_program program = clCreateProgramWithSource(
             context,
             1,  
             &source,
             sourceSize,
             NULL);
   status = clBuildProgram( program, 1, &device, NULL, NULL, NULL );
   if(status != 0)
   {   
     printf("something wrong!!!!!!");
     printf("clBuild failed:%d\n", status);
     char tbuf[0x10000];
     clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0x10000, tbuf,
             NULL);
             printf("\n%s\n", tbuf);
             return 1;
   }
   cl_kernel kernel = NULL;
   kernel = clCreateKernel( program, "Ampli", NULL );
   PWASingNLL::setKernel(kernel);

  double mjpsi=3.097,mka=0.493677,mpi=0.13957;
  double pi=3.1415926;
  double high=mjpsi;
  double low=0-high;
  DPFPWAPoint dphipipi(mka,mka, mpi, mpi, mjpsi, "new_phspdatapipi.dat");
  DPFPWAPoint dphikaka(mka,mka, mka, mka, mjpsi, "new_phspdatakaka.dat");
  RooRealVar v11("v11","11",low,high);
  RooRealVar v12("v12","12",low,high);
  RooRealVar v13("v13","13",low,high);
  RooRealVar v14("v14","14",low,high);
  RooRealVar v21("v21","21",low,high);
  RooRealVar v22("v22","22",low,high);
  RooRealVar v23("v23","23",low,high);
  RooRealVar v24("v24","24",low,high);
  RooRealVar v31("v31","31",low,high);
  RooRealVar v32("v32","32",low,high);
  RooRealVar v33("v33","33",low,high);
  RooRealVar v34("v34","34",low,high);
  RooRealVar v41("v41","41",low,high);
  RooRealVar v42("v42","42",low,high);
  RooRealVar v43("v43","43",low,high);
  RooRealVar v44("v44","44",low,high);
  RooRealVar weight("weight","weight",low,high);











  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  TString indata,bkgdata;
  TString outfitpipi="outpipi.rep";
  TString outfit="outkk.rep";
  TString indatapipi="../Tensor05/fit/phipipi.dat";
  TString indatakaka="../Tensor05/fit/phikaka.dat";
  TString projectfilepipi="resultpipi.root";
  TString projectfilekaka="resultkaka.root";
  bkgdata="kstarkp.dat";
  TString inmckaka="new_phspdatakaka.dat";
  TString inmcpipi="new_phspdatapipi.dat";

  RooArgSet theSet1,theSet2,theSet3;
  theSet1.add(RooArgSet(v11,v12,v13,v14,v21,v22,v23,v24));
  theSet2.add(RooArgSet(v31,v32,v33,v34,v41,v42,v43,v44));
  theSet3.add(RooArgSet(weight));
  RooArgSet theSet4(theSet1,theSet2,"");
  RooArgSet theSet(theSet4,theSet3,"");
  RooDataSet *datadatak = RooDataSet::read(indatakaka,theSet);

//??????????????????????
   Int_t Nre = datadatak->numEntries();
   PWAPdf::NreKa = Nre;
//??????????????????????

   double_t *bfDTks_f      = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkp2       = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkB112     = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkB2f      = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkB1f      = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkB2psi    = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkB4psi    = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkT1u12_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkT1u12_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf021_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf021_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkT1u34_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkT1u34_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkApf021_1 = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkApf021_2 = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf201_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf201_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf221_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf221_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf222_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf222_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf223_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf223_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf243_1  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkAf243_2  = (double_t *)malloc(Nre * sizeof(double_t));
   double_t *bfDTkW        = (double_t *)malloc(Nre * sizeof(double_t));
   
    Double_t s_f,     p2,      B1_12,
             B2f,     B1f,     B2psi,    B4psi,
             T1u12_1, T1u12_2, Af021_1,  Af021_2,
             T1u34_1, T1u34_2, Apf021_1, Apf021_2,
			 Af201_1, Af201_2, Af221_1,  Af221_2,
			 Af222_1, Af222_2, Af223_1,  Af223_2,
			 Af243_1, Af243_2, wgt,      num;
            // fx5,fy5,fz5,ft5;
//    FILE *fp = fopen("new_phikaka.dat","r");
    FILE *fp = fopen("../Tensor05/fit/tens_datakk.dat","r");
    if (fp==NULL)
    {printf("can't open input file"); 
//     return;
    }
    else
    {
       Int_t i=0;
       while(fscanf(fp,"%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n",
					   &s_f,     &p2,      &B1_12,
            		   &B2f,     &B1f,     &B2psi,    &B4psi,
            		   &T1u12_1, &T1u12_2, &Af021_1,  &Af021_2,
            		   &T1u34_1, &T1u34_2, &Apf021_1, &Apf021_2,
					   &Af201_1, &Af201_2, &Af221_1,  &Af221_2,
					   &Af222_1, &Af222_2, &Af223_1,  &Af223_2,
					   &Af243_1, &Af243_2, &wgt,      &num
                    )!=EOF)
       {
//				 cout<<fixed<<setprecision(15)<<"s_f: "<<s_f<<endl;
//  cout<<"haha: "<< __LINE__ << endl;
				bfDTks_f[i]      = s_f;     bfDTkp2[i]       = p2;      bfDTkB112[i]     = B1_12;
                bfDTkB2f[i]      = B2f;     bfDTkB1f[i]      = B1f;     bfDTkB2psi[i]    = B2psi;    bfDTkB4psi[i]    = B4psi;
                bfDTkT1u12_1[i]  = T1u12_1; bfDTkT1u12_2[i]  = T1u12_2; bfDTkAf021_1[i]  = Af021_1;  bfDTkAf021_2[i]  = Af021_2;
                bfDTkT1u34_1[i]  = T1u34_1; bfDTkT1u34_2[i]  = T1u34_2; bfDTkApf021_1[i] = Apf021_1; bfDTkApf021_2[i] = Apf021_2;
                bfDTkAf201_1[i]  = Af201_1; bfDTkAf201_2[i]  = Af201_2; bfDTkAf221_1[i]  = Af221_1;  bfDTkAf221_2[i]  = Af221_2;
                bfDTkAf222_1[i]  = Af222_1; bfDTkAf222_2[i]  = Af222_2; bfDTkAf223_1[i]  = Af223_1;  bfDTkAf223_2[i]  = Af223_2;
                bfDTkAf243_1[i]  = Af243_1; bfDTkAf243_2[i]  = Af243_2; bfDTkW[i]        = wgt;
               // datap5[i][0]=fx5;datap5[i][1]=fy5;datap5[i][2]=fz5;datap5[i][3]=ft5;
                i++;
        }
        fclose(fp);
    }
//cl_mem about particle 1
//cl_mem about particle 2
//cl_mem about particle 3
//cl_mem about particle 4
//cl_mem about Weight
   cl_mem clbfDTks_f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTks_f      , &err );
   cl_mem clbfDTkp2       = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkp2       , &err );
   cl_mem clbfDTkB112     = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkB112     , &err );
   cl_mem clbfDTkB2f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkB2f      , &err );
   cl_mem clbfDTkB1f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkB1f      , &err );
   cl_mem clbfDTkB2psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkB2psi    , &err );
   cl_mem clbfDTkB4psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkB4psi    , &err );
   cl_mem clbfDTkT1u12_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkT1u12_1  , &err );
   cl_mem clbfDTkT1u12_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkT1u12_2  , &err );
   cl_mem clbfDTkAf021_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf021_1  , &err );
   cl_mem clbfDTkAf021_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf021_2  , &err );
   cl_mem clbfDTkT1u34_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkT1u34_1  , &err );
   cl_mem clbfDTkT1u34_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkT1u34_2  , &err );
   cl_mem clbfDTkApf021_1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkApf021_1 , &err );
   cl_mem clbfDTkApf021_2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkApf021_2 , &err );
   cl_mem clbfDTkAf201_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf201_1  , &err );
   cl_mem clbfDTkAf201_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf201_2  , &err );
   cl_mem clbfDTkAf221_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf221_1  , &err );
   cl_mem clbfDTkAf221_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf221_2  , &err );
   cl_mem clbfDTkAf222_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf222_1  , &err );
   cl_mem clbfDTkAf222_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf222_2  , &err );
   cl_mem clbfDTkAf223_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf223_1  , &err );
   cl_mem clbfDTkAf223_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf223_2  , &err );
   cl_mem clbfDTkAf243_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf243_1  , &err );
   cl_mem clbfDTkAf243_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkAf243_2  , &err );
   cl_mem clbfDTkW        = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nre*sizeof(double),bfDTkW        , &err );

   PWASingNLL::m_clbfDTks_f      = &clbfDTks_f     ; PWASingNLL::m_clbfDTkp2       = &clbfDTkp2      ; 
   PWASingNLL::m_clbfDTkB112     = &clbfDTkB112    ; PWASingNLL::m_clbfDTkB2f      = &clbfDTkB2f     ; 
   PWASingNLL::m_clbfDTkB1f      = &clbfDTkB1f     ; PWASingNLL::m_clbfDTkB2psi    = &clbfDTkB2psi   ; 
   PWASingNLL::m_clbfDTkB4psi    = &clbfDTkB4psi   ; PWASingNLL::m_clbfDTkT1u12_1  = &clbfDTkT1u12_1 ; 
   PWASingNLL::m_clbfDTkT1u12_2  = &clbfDTkT1u12_2 ; PWASingNLL::m_clbfDTkAf021_1  = &clbfDTkAf021_1 ; 
   PWASingNLL::m_clbfDTkAf021_2  = &clbfDTkAf021_2 ; PWASingNLL::m_clbfDTkT1u34_1  = &clbfDTkT1u34_1 ; 
   PWASingNLL::m_clbfDTkT1u34_2  = &clbfDTkT1u34_2 ; PWASingNLL::m_clbfDTkApf021_1 = &clbfDTkApf021_1;
   PWASingNLL::m_clbfDTkApf021_2 = &clbfDTkApf021_2; PWASingNLL::m_clbfDTkAf201_1  = &clbfDTkAf201_1 ; 
   PWASingNLL::m_clbfDTkAf201_2  = &clbfDTkAf201_2 ; PWASingNLL::m_clbfDTkAf221_1  = &clbfDTkAf221_1 ; 
   PWASingNLL::m_clbfDTkAf221_2  = &clbfDTkAf221_2 ; PWASingNLL::m_clbfDTkAf222_1  = &clbfDTkAf222_1 ; 
   PWASingNLL::m_clbfDTkAf222_2  = &clbfDTkAf222_2 ; PWASingNLL::m_clbfDTkAf223_1  = &clbfDTkAf223_1 ; 
   PWASingNLL::m_clbfDTkAf223_2  = &clbfDTkAf223_2 ; PWASingNLL::m_clbfDTkAf243_1  = &clbfDTkAf243_1 ; 
   PWASingNLL::m_clbfDTkAf243_2  = &clbfDTkAf243_2 ; PWASingNLL::m_clbfDTkW        = &clbfDTkW       ;
  cout<<"haha: succeed inputting Tens_DATAkaka!!!!!!!" << endl;
// datakaka input over;

//  RooArgSet theSet1,theSet2;
//  theSet1.add(RooArgSet(v11,v12,v13,v14,v21,v22,v23,v24));
//  theSet2.add(RooArgSet(v31,v32,v33,v34,v41,v42,v43,v44));
//  RooArgSet theSet4(theSet1,theSet2,"");
//  RooArgSet theSet(theSet4,theSet3,"");
  RooDataSet *datadatap = RooDataSet::read(indatapipi,theSet);

//??????????????????????????////
   Int_t Nrep = datadatap->numEntries();
   PWAPdf::NrePi = Nrep;
//??????????????????????????////

   double_t *bfDTps_f      = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpp2       = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpB112     = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpB2f      = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpB1f      = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpB2psi    = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpB4psi    = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpT1u12_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpT1u12_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf021_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf021_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpT1u34_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpT1u34_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpApf021_1 = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpApf021_2 = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf201_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf201_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf221_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf221_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf222_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf222_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf223_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf223_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf243_1  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpAf243_2  = (double_t *)malloc(Nrep * sizeof(double_t));
   double_t *bfDTpW        = (double_t *)malloc(Nrep * sizeof(double_t));
   
    Double_t s_f02,     p202,      B1_1202,
             B2f02,     B1f02,     B2psi02,    B4psi02,
             T1u12_102, T1u12_202, Af021_102,  Af021_202,
             T1u34_102, T1u34_202, Apf021_102, Apf021_202,
			 Af201_102, Af201_202, Af221_102,  Af221_202,
			 Af222_102, Af222_202, Af223_102,  Af223_202,
			 Af243_102, Af243_202, wgt02,      num02;
            // fx5,fy5,fz5,ft5;
//     fp = fopen("new_phipipi.dat","r");
     fp = fopen("../Tensor05/fit/tens_datapp.dat","r");
    if (fp==NULL)
    {printf("can't open input file"); 
//     return;
    }
    else
    {
       Int_t i=0;
       while(fscanf(fp,"%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n",
					   &s_f02,     &p202,      &B1_1202,
            		   &B2f02,     &B1f02,     &B2psi02,    &B4psi02,
            		   &T1u12_102, &T1u12_202, &Af021_102,  &Af021_202,
            		   &T1u34_102, &T1u34_202, &Apf021_102, &Apf021_202,
					   &Af201_102, &Af201_202, &Af221_102,  &Af221_202,
					   &Af222_102, &Af222_202, &Af223_102,  &Af223_202,
					   &Af243_102, &Af243_202, &wgt02,      &num02
                    )!=EOF)
       {
//  cout<<"haha: "<< __LINE__ << endl;
				bfDTps_f[i]      = s_f02;     bfDTpp2[i]       = p202;      bfDTpB112[i]     = B1_1202;
                bfDTpB2f[i]      = B2f02;     bfDTpB1f[i]      = B1f02;     bfDTpB2psi[i]    = B2psi02;    bfDTpB4psi[i]    = B4psi02;
                bfDTpT1u12_1[i]  = T1u12_102; bfDTpT1u12_2[i]  = T1u12_202; bfDTpAf021_1[i]  = Af021_102;  bfDTpAf021_2[i]  = Af021_202;
                bfDTpT1u34_1[i]  = T1u34_102; bfDTpT1u34_2[i]  = T1u34_202; bfDTpApf021_1[i] = Apf021_102; bfDTpApf021_2[i] = Apf021_202;
                bfDTpAf201_1[i]  = Af201_102; bfDTpAf201_2[i]  = Af201_202; bfDTpAf221_1[i]  = Af221_102;  bfDTpAf221_2[i]  = Af221_202;
                bfDTpAf222_1[i]  = Af222_102; bfDTpAf222_2[i]  = Af222_202; bfDTpAf223_1[i]  = Af223_102;  bfDTpAf223_2[i]  = Af223_202;
                bfDTpAf243_1[i]  = Af243_102; bfDTpAf243_2[i]  = Af243_202; bfDTpW[i]        = wgt02;
                i++;
        }
        fclose(fp);
    }
//cl_mem about particle 1
//cl_mem about particle 2
//cl_mem about particle 3
//cl_mem about particle 4
//cl_mem about Weight
   cl_mem clbfDTps_f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTps_f      , &err );
   cl_mem clbfDTpp2       = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpp2       , &err );
   cl_mem clbfDTpB112     = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpB112     , &err );
   cl_mem clbfDTpB2f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpB2f      , &err );
   cl_mem clbfDTpB1f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpB1f      , &err );
   cl_mem clbfDTpB2psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpB2psi    , &err );
   cl_mem clbfDTpB4psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpB4psi    , &err );
   cl_mem clbfDTpT1u12_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpT1u12_1  , &err );
   cl_mem clbfDTpT1u12_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpT1u12_2  , &err );
   cl_mem clbfDTpAf021_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf021_1  , &err );
   cl_mem clbfDTpAf021_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf021_2  , &err );
   cl_mem clbfDTpT1u34_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpT1u34_1  , &err );
   cl_mem clbfDTpT1u34_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpT1u34_2  , &err );
   cl_mem clbfDTpApf021_1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpApf021_1 , &err );
   cl_mem clbfDTpApf021_2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpApf021_2 , &err );
   cl_mem clbfDTpAf201_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf201_1  , &err );
   cl_mem clbfDTpAf201_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf201_2  , &err );
   cl_mem clbfDTpAf221_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf221_1  , &err );
   cl_mem clbfDTpAf221_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf221_2  , &err );
   cl_mem clbfDTpAf222_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf222_1  , &err );
   cl_mem clbfDTpAf222_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf222_2  , &err );
   cl_mem clbfDTpAf223_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf223_1  , &err );
   cl_mem clbfDTpAf223_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf223_2  , &err );
   cl_mem clbfDTpAf243_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf243_1  , &err );
   cl_mem clbfDTpAf243_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpAf243_2  , &err );
   cl_mem clbfDTpW        = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrep*sizeof(double),bfDTpW        , &err );

   PWASingNLL::m_clbfDTps_f      = &clbfDTps_f     ; PWASingNLL::m_clbfDTpp2       = &clbfDTpp2      ; 
   PWASingNLL::m_clbfDTpB112     = &clbfDTpB112    ; PWASingNLL::m_clbfDTpB2f      = &clbfDTpB2f     ; 
   PWASingNLL::m_clbfDTpB1f      = &clbfDTpB1f     ; PWASingNLL::m_clbfDTpB2psi    = &clbfDTpB2psi   ; 
   PWASingNLL::m_clbfDTpB4psi    = &clbfDTpB4psi   ; PWASingNLL::m_clbfDTpT1u12_1  = &clbfDTpT1u12_1 ; 
   PWASingNLL::m_clbfDTpT1u12_2  = &clbfDTpT1u12_2 ; PWASingNLL::m_clbfDTpAf021_1  = &clbfDTpAf021_1 ; 
   PWASingNLL::m_clbfDTpAf021_2  = &clbfDTpAf021_2 ; PWASingNLL::m_clbfDTpT1u34_1  = &clbfDTpT1u34_1 ; 
   PWASingNLL::m_clbfDTpT1u34_2  = &clbfDTpT1u34_2 ; PWASingNLL::m_clbfDTpApf021_1 = &clbfDTpApf021_1;
   PWASingNLL::m_clbfDTpApf021_2 = &clbfDTpApf021_2; PWASingNLL::m_clbfDTpAf201_1  = &clbfDTpAf201_1 ; 
   PWASingNLL::m_clbfDTpAf201_2  = &clbfDTpAf201_2 ; PWASingNLL::m_clbfDTpAf221_1  = &clbfDTpAf221_1 ; 
   PWASingNLL::m_clbfDTpAf221_2  = &clbfDTpAf221_2 ; PWASingNLL::m_clbfDTpAf222_1  = &clbfDTpAf222_1 ; 
   PWASingNLL::m_clbfDTpAf222_2  = &clbfDTpAf222_2 ; PWASingNLL::m_clbfDTpAf223_1  = &clbfDTpAf223_1 ; 
   PWASingNLL::m_clbfDTpAf223_2  = &clbfDTpAf223_2 ; PWASingNLL::m_clbfDTpAf243_1  = &clbfDTpAf243_1 ; 
   PWASingNLL::m_clbfDTpAf243_2  = &clbfDTpAf243_2 ; PWASingNLL::m_clbfDTpW        = &clbfDTpW       ;

  cout<<"haha: succeed inputting DATApipi!!!!!!!" << endl;

//  RooArgSet theSet1mc,theSet2mc;
//  theSet1mc.add(RooArgSet(v11,v12,v13,v14,v21,v22,v23,v24));
//  theSet2mc.add(RooArgSet(v31,v32,v33,v34,v41,v42,v43,v44));
//  RooArgSet theSet3mc(theSet1mc,theSet2mc,"");
//
//  RooDataSet *mcmck = RooDataSet::read(inmckaka,theSet3mc);
//
//??????????????????????????////
//   Int_t Nrek = mcmck->numEntries();
   Int_t Nrek = Nphsmc;
//??????????????????????????////

   double_t *bfMCks_f      = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkp2       = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkB112     = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkB2f      = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkB1f      = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkB2psi    = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkB4psi    = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkT1u12_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkT1u12_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf021_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf021_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkT1u34_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkT1u34_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkApf021_1 = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkApf021_2 = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf201_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf201_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf221_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf221_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf222_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf222_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf223_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf223_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf243_1  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkAf243_2  = (double_t *)malloc(Nrek * sizeof(double_t));
   double_t *bfMCkW        = (double_t *)malloc(Nrek * sizeof(double_t));
    Double_t s_f03,     p203,      B1_1203,
             B2f03,     B1f03,     B2psi03,    B4psi03,
             T1u12_103, T1u12_203, Af021_103,  Af021_203,
             T1u34_103, T1u34_203, Apf021_103, Apf021_203,
			 Af201_103, Af201_203, Af221_103,  Af221_203,
			 Af222_103, Af222_203, Af223_103,  Af223_203,
			 Af243_103, Af243_203, wgt03,      num03;
            // fx5,fy5,fz5,ft5;
//    FILE *fp = fopen("phspdatapipi.dat","r");
//     fp = fopen("new_phspdatakaka.dat","r");
     fp = fopen("../Tensor05/fit/tens_PHSPkk.dat","r");
    if (fp==NULL)
    {printf("can't open input file"); 
//     return;
    }
    else
    {
       Int_t i=0;
       while(fscanf(fp,"%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n",
					   &s_f03,     &p203,      &B1_1203,
            		   &B2f03,     &B1f03,     &B2psi03,    &B4psi03,
            		   &T1u12_103, &T1u12_203, &Af021_103,  &Af021_203,
            		   &T1u34_103, &T1u34_203, &Apf021_103, &Apf021_203,
					   &Af201_103, &Af201_203, &Af221_103,  &Af221_203,
					   &Af222_103, &Af222_203, &Af223_103,  &Af223_203,
					   &Af243_103, &Af243_203, &wgt03,      &num03
                    )!=EOF)
       {
//  cout<<"haha: "<< __LINE__ << endl;
				bfMCks_f[i]      = s_f03;     bfMCkp2[i]       = p203;      bfMCkB112[i]     = B1_1203;
                bfMCkB2f[i]      = B2f03;     bfMCkB1f[i]      = B1f03;     bfMCkB2psi[i]    = B2psi03;    bfMCkB4psi[i]    = B4psi03;
                bfMCkT1u12_1[i]  = T1u12_103; bfMCkT1u12_2[i]  = T1u12_203; bfMCkAf021_1[i]  = Af021_103;  bfMCkAf021_2[i]  = Af021_203;
                bfMCkT1u34_1[i]  = T1u34_103; bfMCkT1u34_2[i]  = T1u34_203; bfMCkApf021_1[i] = Apf021_103; bfMCkApf021_2[i] = Apf021_203;
                bfMCkAf201_1[i]  = Af201_103; bfMCkAf201_2[i]  = Af201_203; bfMCkAf221_1[i]  = Af221_103;  bfMCkAf221_2[i]  = Af221_203;
                bfMCkAf222_1[i]  = Af222_103; bfMCkAf222_2[i]  = Af222_203; bfMCkAf223_1[i]  = Af223_103;  bfMCkAf223_2[i]  = Af223_203;
                bfMCkAf243_1[i]  = Af243_103; bfMCkAf243_2[i]  = Af243_203; bfMCkW[i]        = wgt03;
               // mck5[i][0]=fx5;mck5[i][1]=fy5;mck5[i][2]=fz5;mck5[i][3]=ft5;
                i++;
        }
        fclose(fp);
    }
//cl_mem about particle 1
//cl_mem about particle 2
//cl_mem about particle 3
//cl_mem about particle 4
   cl_mem clbfMCks_f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCks_f      , &err );
   cl_mem clbfMCkp2       = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkp2       , &err );
   cl_mem clbfMCkB112     = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkB112     , &err );
   cl_mem clbfMCkB2f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkB2f      , &err );
   cl_mem clbfMCkB1f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkB1f      , &err );
   cl_mem clbfMCkB2psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkB2psi    , &err );
   cl_mem clbfMCkB4psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkB4psi    , &err );
   cl_mem clbfMCkT1u12_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkT1u12_1  , &err );
   cl_mem clbfMCkT1u12_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkT1u12_2  , &err );
   cl_mem clbfMCkAf021_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf021_1  , &err );
   cl_mem clbfMCkAf021_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf021_2  , &err );
   cl_mem clbfMCkT1u34_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkT1u34_1  , &err );
   cl_mem clbfMCkT1u34_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkT1u34_2  , &err );
   cl_mem clbfMCkApf021_1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkApf021_1 , &err );
   cl_mem clbfMCkApf021_2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkApf021_2 , &err );
   cl_mem clbfMCkAf201_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf201_1  , &err );
   cl_mem clbfMCkAf201_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf201_2  , &err );
   cl_mem clbfMCkAf221_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf221_1  , &err );
   cl_mem clbfMCkAf221_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf221_2  , &err );
   cl_mem clbfMCkAf222_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf222_1  , &err );
   cl_mem clbfMCkAf222_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf222_2  , &err );
   cl_mem clbfMCkAf223_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf223_1  , &err );
   cl_mem clbfMCkAf223_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf223_2  , &err );
   cl_mem clbfMCkAf243_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf243_1  , &err );
   cl_mem clbfMCkAf243_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkAf243_2  , &err );
   cl_mem clbfMCkW        = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, Nrek*sizeof(double),bfMCkW        , &err );
   
   PWASingNLL::m_clbfMCks_f      = &clbfMCks_f     ; PWASingNLL::m_clbfMCkp2       = &clbfMCkp2      ; 
   PWASingNLL::m_clbfMCkB112     = &clbfMCkB112    ; PWASingNLL::m_clbfMCkB2f      = &clbfMCkB2f     ; 
   PWASingNLL::m_clbfMCkB1f      = &clbfMCkB1f     ; PWASingNLL::m_clbfMCkB2psi    = &clbfMCkB2psi   ; 
   PWASingNLL::m_clbfMCkB4psi    = &clbfMCkB4psi   ; PWASingNLL::m_clbfMCkT1u12_1  = &clbfMCkT1u12_1 ; 
   PWASingNLL::m_clbfMCkT1u12_2  = &clbfMCkT1u12_2 ; PWASingNLL::m_clbfMCkAf021_1  = &clbfMCkAf021_1 ; 
   PWASingNLL::m_clbfMCkAf021_2  = &clbfMCkAf021_2 ; PWASingNLL::m_clbfMCkT1u34_1  = &clbfMCkT1u34_1 ; 
   PWASingNLL::m_clbfMCkT1u34_2  = &clbfMCkT1u34_2 ; PWASingNLL::m_clbfMCkApf021_1 = &clbfMCkApf021_1;
   PWASingNLL::m_clbfMCkApf021_2 = &clbfMCkApf021_2; PWASingNLL::m_clbfMCkAf201_1  = &clbfMCkAf201_1 ; 
   PWASingNLL::m_clbfMCkAf201_2  = &clbfMCkAf201_2 ; PWASingNLL::m_clbfMCkAf221_1  = &clbfMCkAf221_1 ; 
   PWASingNLL::m_clbfMCkAf221_2  = &clbfMCkAf221_2 ; PWASingNLL::m_clbfMCkAf222_1  = &clbfMCkAf222_1 ; 
   PWASingNLL::m_clbfMCkAf222_2  = &clbfMCkAf222_2 ; PWASingNLL::m_clbfMCkAf223_1  = &clbfMCkAf223_1 ; 
   PWASingNLL::m_clbfMCkAf223_2  = &clbfMCkAf223_2 ; PWASingNLL::m_clbfMCkAf243_1  = &clbfMCkAf243_1 ; 
   PWASingNLL::m_clbfMCkAf243_2  = &clbfMCkAf243_2 ; PWASingNLL::m_clbfMCkW        = &clbfMCkW       ;
  cout<<"haha: succeed inputting MCkaka!!!!!!!" << endl;


//  RooDataSet *mcmcp = RooDataSet::read(inmcpipi,theSet3mc);

//   Int_t NreMCp = mcmcp->numEntries();
   Int_t NreMCp = Nphsmc;
   double_t *bfMCps_f      = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpp2       = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpB112     = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpB2f      = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpB1f      = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpB2psi    = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpB4psi    = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpT1u12_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpT1u12_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf021_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf021_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpT1u34_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpT1u34_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpApf021_1 = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpApf021_2 = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf201_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf201_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf221_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf221_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf222_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf222_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf223_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf223_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf243_1  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpAf243_2  = (double_t *)malloc(NreMCp * sizeof(double_t));
   double_t *bfMCpW        = (double_t *)malloc(NreMCp * sizeof(double_t));

   
    Double_t s_f04,     p204,      B1_1204,
             B2f04,     B1f04,     B2psi04,    B4psi04,
             T1u12_104, T1u12_204, Af021_104,  Af021_204,
             T1u34_104, T1u34_204, Apf021_104, Apf021_204,
			 Af201_104, Af201_204, Af221_104,  Af221_204,
			 Af222_104, Af222_204, Af223_104,  Af223_204,
			 Af243_104, Af243_204, wgt04,      num04;
            // fx5,fy5,fz5,ft5;
//    FILE *fp = fopen("phspdatapipi.dat","r");
//     fp = fopen("new_phspdatapipi.dat","r");
     fp = fopen("../Tensor05/fit/tens_PHSPpp.dat","r");
    if (fp==NULL)
    {printf("can't open input file"); 
//     return;
    }
    else
    {
       Int_t i=0;
       while(fscanf(fp,"%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n%lf%lf%lf%lf\n",
					   &s_f04,     &p204,      &B1_1204,
            		   &B2f04,     &B1f04,     &B2psi04,    &B4psi04,
            		   &T1u12_104, &T1u12_204, &Af021_104,  &Af021_204,
            		   &T1u34_104, &T1u34_204, &Apf021_104, &Apf021_204,
					   &Af201_104, &Af201_204, &Af221_104,  &Af221_204,
					   &Af222_104, &Af222_204, &Af223_104,  &Af223_204,
					   &Af243_104, &Af243_204, &wgt04,    &num04
                    )!=EOF)
       {
//  cout<<"haha: "<< __LINE__ << endl;

				bfMCps_f[i]      = s_f04;     bfMCpp2[i]       = p204;      bfMCpB112[i]     = B1_1204;
                bfMCpB2f[i]      = B2f04;     bfMCpB1f[i]      = B1f04;     bfMCpB2psi[i]    = B2psi04;    bfMCpB4psi[i]    = B4psi04;
                bfMCpT1u12_1[i]  = T1u12_104; bfMCpT1u12_2[i]  = T1u12_204; bfMCpAf021_1[i]  = Af021_104;  bfMCpAf021_2[i]  = Af021_204;
                bfMCpT1u34_1[i]  = T1u34_104; bfMCpT1u34_2[i]  = T1u34_204; bfMCpApf021_1[i] = Apf021_104; bfMCpApf021_2[i] = Apf021_204;
                bfMCpAf201_1[i]  = Af201_104; bfMCpAf201_2[i]  = Af201_204; bfMCpAf221_1[i]  = Af221_104;  bfMCpAf221_2[i]  = Af221_204;
                bfMCpAf222_1[i]  = Af222_104; bfMCpAf222_2[i]  = Af222_204; bfMCpAf223_1[i]  = Af223_104;  bfMCpAf223_2[i]  = Af223_204;
                bfMCpAf243_1[i]  = Af243_104; bfMCpAf243_2[i]  = Af243_204; bfMCpW[i]        = wgt03;
//                bufmcp1t[i] = ft104; bufmcp1x[i] = fx104; bufmcp1y[i] = fy104; bufmcp1z[i] = fz104;
//                bufmcp2t[i] = ft204; bufmcp2x[i] = fx204; bufmcp2y[i] = fy204; bufmcp2z[i] = fz204;
//                bufmcp3t[i] = ft304; bufmcp3x[i] = fx304; bufmcp3y[i] = fy304; bufmcp3z[i] = fz304;
//                bufmcp4t[i] = ft404; bufmcp4x[i] = fx404; bufmcp4y[i] = fy404; bufmcp4z[i] = fz404;
//				bufmcpW[i]  = mcpW;
               // mcp5[i][0]=fx5;mcp5[i][1]=fy5;mcp5[i][2]=fz5;mcp5[i][3]=ft5;
                i++;
        }
        fclose(fp);
    }
//cl_mem about particle 1
//cl_mem about particle 2
//cl_mem about particle 3
//cl_mem about particle 4
//cl_mem about Weight
   cl_mem clbfMCps_f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCps_f      , &err );
   cl_mem clbfMCpp2       = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpp2       , &err );
   cl_mem clbfMCpB112     = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpB112     , &err );
   cl_mem clbfMCpB2f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpB2f      , &err );
   cl_mem clbfMCpB1f      = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpB1f      , &err );
   cl_mem clbfMCpB2psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpB2psi    , &err );
   cl_mem clbfMCpB4psi    = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpB4psi    , &err );
   cl_mem clbfMCpT1u12_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpT1u12_1  , &err );
   cl_mem clbfMCpT1u12_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpT1u12_2  , &err );
   cl_mem clbfMCpAf021_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf021_1  , &err );
   cl_mem clbfMCpAf021_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf021_2  , &err );
   cl_mem clbfMCpT1u34_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpT1u34_1  , &err );
   cl_mem clbfMCpT1u34_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpT1u34_2  , &err );
   cl_mem clbfMCpApf021_1 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpApf021_1 , &err );
   cl_mem clbfMCpApf021_2 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpApf021_2 , &err );
   cl_mem clbfMCpAf201_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf201_1  , &err );
   cl_mem clbfMCpAf201_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf201_2  , &err );
   cl_mem clbfMCpAf221_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf221_1  , &err );
   cl_mem clbfMCpAf221_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf221_2  , &err );
   cl_mem clbfMCpAf222_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf222_1  , &err );
   cl_mem clbfMCpAf222_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf222_2  , &err );
   cl_mem clbfMCpAf223_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf223_1  , &err );
   cl_mem clbfMCpAf223_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf223_2  , &err );
   cl_mem clbfMCpAf243_1  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf243_1  , &err );
   cl_mem clbfMCpAf243_2  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpAf243_2  , &err );
   cl_mem clbfMCpW        = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, NreMCp*sizeof(double),bfMCpW        , &err );

   PWASingNLL::m_clbfMCps_f      = &clbfMCps_f     ; PWASingNLL::m_clbfMCpp2       = &clbfMCpp2      ; 
   PWASingNLL::m_clbfMCpB112     = &clbfMCpB112    ; PWASingNLL::m_clbfMCpB2f      = &clbfMCpB2f     ; 
   PWASingNLL::m_clbfMCpB1f      = &clbfMCpB1f     ; PWASingNLL::m_clbfMCpB2psi    = &clbfMCpB2psi   ; 
   PWASingNLL::m_clbfMCpB4psi    = &clbfMCpB4psi   ; PWASingNLL::m_clbfMCpT1u12_1  = &clbfMCpT1u12_1 ; 
   PWASingNLL::m_clbfMCpT1u12_2  = &clbfMCpT1u12_2 ; PWASingNLL::m_clbfMCpAf021_1  = &clbfMCpAf021_1 ; 
   PWASingNLL::m_clbfMCpAf021_2  = &clbfMCpAf021_2 ; PWASingNLL::m_clbfMCpT1u34_1  = &clbfMCpT1u34_1 ; 
   PWASingNLL::m_clbfMCpT1u34_2  = &clbfMCpT1u34_2 ; PWASingNLL::m_clbfMCpApf021_1 = &clbfMCpApf021_1;
   PWASingNLL::m_clbfMCpApf021_2 = &clbfMCpApf021_2; PWASingNLL::m_clbfMCpAf201_1  = &clbfMCpAf201_1 ; 
   PWASingNLL::m_clbfMCpAf201_2  = &clbfMCpAf201_2 ; PWASingNLL::m_clbfMCpAf221_1  = &clbfMCpAf221_1 ; 
   PWASingNLL::m_clbfMCpAf221_2  = &clbfMCpAf221_2 ; PWASingNLL::m_clbfMCpAf222_1  = &clbfMCpAf222_1 ; 
   PWASingNLL::m_clbfMCpAf222_2  = &clbfMCpAf222_2 ; PWASingNLL::m_clbfMCpAf223_1  = &clbfMCpAf223_1 ; 
   PWASingNLL::m_clbfMCpAf223_2  = &clbfMCpAf223_2 ; PWASingNLL::m_clbfMCpAf243_1  = &clbfMCpAf243_1 ; 
   PWASingNLL::m_clbfMCpAf243_2  = &clbfMCpAf243_2 ; PWASingNLL::m_clbfMCpW        = &clbfMCpW       ;
  cout<<"haha: succeed inputting MCpipi!!!!!!!" << endl;

  RooArgSet theSet1d,theSet2d,theSet3d;
  theSet1d.add(RooArgSet(v11,v12,v13,v14,v21,v22,v23,v24));
  theSet2d.add(RooArgSet(v31,v32,v33,v34,v41,v42,v43,v44));
  theSet3d.add(RooArgSet(weight));
  RooArgSet theSet4d(theSet1d,theSet2d,"");
  RooArgSet theSetd(theSet4d,theSet3d,"");

  cout<<"-----------------"<<endl;
  RooDataSet *data11 = RooDataSet::read(indatapipi,theSetd);
  data11->Print();
  RooDataSet *datapipi= new RooDataSet(data11->GetName(),data11->GetTitle(),data11,*data11->get(),0,weight.GetName());
  datapipi->Print();


  PWAPdf pdfpipi("pdfpipi","pdfpipi",v11,v12,v13,v14,v21,v22,v23,v24,v31,v32,v33,v34,v41,v42,v43,v44,&dphipipi);

	/*****************************Adding pdfpipi begin***********************************/
	/*****************************Adding pdfpipi end  ***********************************/

  PWASingNLL::setpdfpi(&pdfpipi);
  
  cout<<"-----------------"<<endl;
  RooDataSet *data22 = RooDataSet::read(indatakaka,theSetd);
  data22->Print();
  RooDataSet *datakaka= new RooDataSet(data22->GetName(),data22->GetTitle(),data22,*data22->get(),0,weight.GetName());
  datakaka->Print();

  PWAPdf pdfkaka("pdfkaka","pdfkaka",v11,v12,v13,v14,v21,v22,v23,v24,v31,v32,v33,v34,v41,v42,v43,v44,&dphikaka);

	/*****************************Adding pdfkaka begin***********************************/
	/*****************************Adding pdfkaka end  ***********************************/

  PWASingNLL::setpdfka(&pdfkaka);


  RooCategory kapi("kapi","kapi");
  kapi.defineType("phipipi");
  kapi.defineType("phikaka");
  
  RooDataSet combdata("combdata","combined data",theSetd, Index(kapi),Import("phipipi",*datapipi),Import("phikaka",*datakaka),WeightVar(weight));
//  RooDataSet combdata("combdata","combined data",theSetd, Index(kapi),Import("phipipi",*datapipi),Import("phikaka",*datakaka));

  RooSimultaneous simPdf("simPdf","simultaneous pdf",kapi);
  simPdf.addPdf(pdfpipi,"phipipi");
  simPdf.addPdf(pdfkaka,"phikaka");

   cout <<endl;
   cout <<endl;
   time_t timep1;
   time (&timep1);
   cout << "[PWA] ->>>>>>>>>> Now Fitting ........." << endl;
   cout<<"BE4, UNFITTED TIME: "<<ctime(&timep1)<<endl;

//  RooFitResult* res = simPdf.fitTo(combdata,Save(),RooFit::NumCPU(6),RooFit::Optimize(0));
//  DPFNLLVar nll("nll","nll",simPdf,combdata, SumW2Error(kTRUE));
  DPFNLLVar nll("nll","nll",simPdf,combdata, SumW2Error(kTRUE));
//  cout<<"hello3"<<endl;
  RooMinuit m(nll) ;
//  // Disable verbose logging
//  m.setVerbose(kFALSE) ;
  m.setVerbose(kTRUE) ;
//  cout<<"hello5"<<endl;
  m.migrad() ;
//  cout<<"hello6"<<endl;
//  // Print values of all paramaters, that reflect values (and error estimates)
//  // that are back propagated from MINUIT
//
//
//  // Run HESSE to calculate errors from d2L/dp2
  m.hesse() ;
//  
//  RooFitResult* res = m.save();
//  m.minos();		  
  ////////////////////////////////////////////////////////////
  cout << "[PWA] ->>>>>>>>>> Now Fitting ........." << endl;
  RooFitResult *resSim;
  resSim = m.save();
  resSim->Print("v");
////////////////////put matrix, value and error in fitresult.root///////////////////////////
  TFile fr("fitresult.root","RECREATE");
  resSim->Write("fitresult");
  fr.Close();

  time_t timep2;
  time (&timep2);
  cout << "[PWA] ->>>>>>>>>> Fitting is OVER ........." << endl;
  cout<<"AFTER, FITTED TIME: "<<ctime(&timep2)<<endl;
  //if (_sigdefined) res = pdf.fitTo(*data,RooFit::Save(kTRUE),RooFit::Minos(kFALSE));
  //if (EffGdefined) res = effgenpdf.fitTo(*data,RooFit::Save(kTRUE),RooFit::Minos(kFALSE));
  //if (EffAdefined) res = effaccpdf.fitTo(*data,RooFit::Save(kTRUE),RooFit::Minos(kFALSE));

  cout<<"[PWA]>>>>>>>>>>>>>>>>>CL_Release Something......................"<<endl;
if(bfDTks_f     ) free(bfDTks_f     ) ; if(bfDTkp2      ) free(bfDTkp2      ) ; 
if(bfDTkB112    ) free(bfDTkB112    ) ; if(bfDTkB2f     ) free(bfDTkB2f     ) ; 
if(bfDTkB1f     ) free(bfDTkB1f     ) ; if(bfDTkB2psi   ) free(bfDTkB2psi   ) ; 
if(bfDTkB4psi   ) free(bfDTkB4psi   ) ; if(bfDTkT1u12_1 ) free(bfDTkT1u12_1 ) ; 
if(bfDTkT1u12_2 ) free(bfDTkT1u12_2 ) ; if(bfDTkAf021_1 ) free(bfDTkAf021_1 ) ; 
if(bfDTkAf021_2 ) free(bfDTkAf021_2 ) ; if(bfDTkT1u34_1 ) free(bfDTkT1u34_1 ) ; 
if(bfDTkT1u34_2 ) free(bfDTkT1u34_2 ) ; if(bfDTkApf021_1) free(bfDTkApf021_1) ;
if(bfDTkApf021_2) free(bfDTkApf021_2) ; if(bfDTkAf201_1 ) free(bfDTkAf201_1 ) ; 
if(bfDTkAf201_2 ) free(bfDTkAf201_2 ) ; if(bfDTkAf221_1 ) free(bfDTkAf221_1 ) ; 
if(bfDTkAf221_2 ) free(bfDTkAf221_2 ) ; if(bfDTkAf222_1 ) free(bfDTkAf222_1 ) ; 
if(bfDTkAf222_2 ) free(bfDTkAf222_2 ) ; if(bfDTkAf223_1 ) free(bfDTkAf223_1 ) ; 
if(bfDTkAf223_2 ) free(bfDTkAf223_2 ) ; if(bfDTkAf243_1 ) free(bfDTkAf243_1 ) ; 
if(bfDTkAf243_2 ) free(bfDTkAf243_2 ) ; if(bfDTkW       ) free(bfDTkW       ) ;

if(bfDTps_f     ) free(bfDTps_f     ) ; if(bfDTpp2      ) free(bfDTpp2      ) ; 
if(bfDTpB112    ) free(bfDTpB112    ) ; if(bfDTpB2f     ) free(bfDTpB2f     ) ; 
if(bfDTpB1f     ) free(bfDTpB1f     ) ; if(bfDTpB2psi   ) free(bfDTpB2psi   ) ; 
if(bfDTpB4psi   ) free(bfDTpB4psi   ) ; if(bfDTpT1u12_1 ) free(bfDTpT1u12_1 ) ; 
if(bfDTpT1u12_2 ) free(bfDTpT1u12_2 ) ; if(bfDTpAf021_1 ) free(bfDTpAf021_1 ) ; 
if(bfDTpAf021_2 ) free(bfDTpAf021_2 ) ; if(bfDTpT1u34_1 ) free(bfDTpT1u34_1 ) ; 
if(bfDTpT1u34_2 ) free(bfDTpT1u34_2 ) ; if(bfDTpApf021_1) free(bfDTpApf021_1) ;
if(bfDTpApf021_2) free(bfDTpApf021_2) ; if(bfDTpAf201_1 ) free(bfDTpAf201_1 ) ; 
if(bfDTpAf201_2 ) free(bfDTpAf201_2 ) ; if(bfDTpAf221_1 ) free(bfDTpAf221_1 ) ; 
if(bfDTpAf221_2 ) free(bfDTpAf221_2 ) ; if(bfDTpAf222_1 ) free(bfDTpAf222_1 ) ; 
if(bfDTpAf222_2 ) free(bfDTpAf222_2 ) ; if(bfDTpAf223_1 ) free(bfDTpAf223_1 ) ; 
if(bfDTpAf223_2 ) free(bfDTpAf223_2 ) ; if(bfDTpAf243_1 ) free(bfDTpAf243_1 ) ; 
if(bfDTpAf243_2 ) free(bfDTpAf243_2 ) ; if(bfDTpW       ) free(bfDTpW       ) ;

if(bfMCks_f     ) free(bfMCks_f     ) ; if(bfMCkp2      ) free(bfMCkp2      ) ; 
if(bfMCkB112    ) free(bfMCkB112    ) ; if(bfMCkB2f     ) free(bfMCkB2f     ) ; 
if(bfMCkB1f     ) free(bfMCkB1f     ) ; if(bfMCkB2psi   ) free(bfMCkB2psi   ) ; 
if(bfMCkB4psi   ) free(bfMCkB4psi   ) ; if(bfMCkT1u12_1 ) free(bfMCkT1u12_1 ) ; 
if(bfMCkT1u12_2 ) free(bfMCkT1u12_2 ) ; if(bfMCkAf021_1 ) free(bfMCkAf021_1 ) ; 
if(bfMCkAf021_2 ) free(bfMCkAf021_2 ) ; if(bfMCkT1u34_1 ) free(bfMCkT1u34_1 ) ; 
if(bfMCkT1u34_2 ) free(bfMCkT1u34_2 ) ; if(bfMCkApf021_1) free(bfMCkApf021_1) ;
if(bfMCkApf021_2) free(bfMCkApf021_2) ; if(bfMCkAf201_1 ) free(bfMCkAf201_1 ) ; 
if(bfMCkAf201_2 ) free(bfMCkAf201_2 ) ; if(bfMCkAf221_1 ) free(bfMCkAf221_1 ) ; 
if(bfMCkAf221_2 ) free(bfMCkAf221_2 ) ; if(bfMCkAf222_1 ) free(bfMCkAf222_1 ) ; 
if(bfMCkAf222_2 ) free(bfMCkAf222_2 ) ; if(bfMCkAf223_1 ) free(bfMCkAf223_1 ) ; 
if(bfMCkAf223_2 ) free(bfMCkAf223_2 ) ; if(bfMCkAf243_1 ) free(bfMCkAf243_1 ) ; 
if(bfMCkAf243_2 ) free(bfMCkAf243_2 ) ; if(bfMCkW       ) free(bfMCkW       ) ;

if(bfMCps_f     ) free(bfMCps_f     ) ; if(bfMCpp2      ) free(bfMCpp2      ) ; 
if(bfMCpB112    ) free(bfMCpB112    ) ; if(bfMCpB2f     ) free(bfMCpB2f     ) ; 
if(bfMCpB1f     ) free(bfMCpB1f     ) ; if(bfMCpB2psi   ) free(bfMCpB2psi   ) ; 
if(bfMCpB4psi   ) free(bfMCpB4psi   ) ; if(bfMCpT1u12_1 ) free(bfMCpT1u12_1 ) ; 
if(bfMCpT1u12_2 ) free(bfMCpT1u12_2 ) ; if(bfMCpAf021_1 ) free(bfMCpAf021_1 ) ; 
if(bfMCpAf021_2 ) free(bfMCpAf021_2 ) ; if(bfMCpT1u34_1 ) free(bfMCpT1u34_1 ) ; 
if(bfMCpT1u34_2 ) free(bfMCpT1u34_2 ) ; if(bfMCpApf021_1) free(bfMCpApf021_1) ;
if(bfMCpApf021_2) free(bfMCpApf021_2) ; if(bfMCpAf201_1 ) free(bfMCpAf201_1 ) ; 
if(bfMCpAf201_2 ) free(bfMCpAf201_2 ) ; if(bfMCpAf221_1 ) free(bfMCpAf221_1 ) ; 
if(bfMCpAf221_2 ) free(bfMCpAf221_2 ) ; if(bfMCpAf222_1 ) free(bfMCpAf222_1 ) ; 
if(bfMCpAf222_2 ) free(bfMCpAf222_2 ) ; if(bfMCpAf223_1 ) free(bfMCpAf223_1 ) ; 
if(bfMCpAf223_2 ) free(bfMCpAf223_2 ) ; if(bfMCpAf243_1 ) free(bfMCpAf243_1 ) ; 
if(bfMCpAf243_2 ) free(bfMCpAf243_2 ) ; if(bfMCpW       ) free(bfMCpW       ) ;

clReleaseMemObject(clbfDTks_f     ); clReleaseMemObject(clbfDTkp2      ); 
clReleaseMemObject(clbfDTkB112    ); clReleaseMemObject(clbfDTkB2f     ); 
clReleaseMemObject(clbfDTkB1f     ); clReleaseMemObject(clbfDTkB2psi   ); 
clReleaseMemObject(clbfDTkB4psi   ); clReleaseMemObject(clbfDTkT1u12_1 ); 
clReleaseMemObject(clbfDTkT1u12_2 ); clReleaseMemObject(clbfDTkAf021_1 ); 
clReleaseMemObject(clbfDTkAf021_2 ); clReleaseMemObject(clbfDTkT1u34_1 ); 
clReleaseMemObject(clbfDTkT1u34_2 ); clReleaseMemObject(clbfDTkApf021_1);
clReleaseMemObject(clbfDTkApf021_2); clReleaseMemObject(clbfDTkAf201_1 ); 
clReleaseMemObject(clbfDTkAf201_2 ); clReleaseMemObject(clbfDTkAf221_1 ); 
clReleaseMemObject(clbfDTkAf221_2 ); clReleaseMemObject(clbfDTkAf222_1 ); 
clReleaseMemObject(clbfDTkAf222_2 ); clReleaseMemObject(clbfDTkAf223_1 ); 
clReleaseMemObject(clbfDTkAf223_2 ); clReleaseMemObject(clbfDTkAf243_1 ); 
clReleaseMemObject(clbfDTkAf243_2 ); clReleaseMemObject(clbfDTkW       );

clReleaseMemObject(clbfDTps_f     ); clReleaseMemObject(clbfDTpp2      ); 
clReleaseMemObject(clbfDTpB112    ); clReleaseMemObject(clbfDTpB2f     ); 
clReleaseMemObject(clbfDTpB1f     ); clReleaseMemObject(clbfDTpB2psi   ); 
clReleaseMemObject(clbfDTpB4psi   ); clReleaseMemObject(clbfDTpT1u12_1 ); 
clReleaseMemObject(clbfDTpT1u12_2 ); clReleaseMemObject(clbfDTpAf021_1 ); 
clReleaseMemObject(clbfDTpAf021_2 ); clReleaseMemObject(clbfDTpT1u34_1 ); 
clReleaseMemObject(clbfDTpT1u34_2 ); clReleaseMemObject(clbfDTpApf021_1);
clReleaseMemObject(clbfDTpApf021_2); clReleaseMemObject(clbfDTpAf201_1 ); 
clReleaseMemObject(clbfDTpAf201_2 ); clReleaseMemObject(clbfDTpAf221_1 ); 
clReleaseMemObject(clbfDTpAf221_2 ); clReleaseMemObject(clbfDTpAf222_1 ); 
clReleaseMemObject(clbfDTpAf222_2 ); clReleaseMemObject(clbfDTpAf223_1 ); 
clReleaseMemObject(clbfDTpAf223_2 ); clReleaseMemObject(clbfDTpAf243_1 ); 
clReleaseMemObject(clbfDTpAf243_2 ); clReleaseMemObject(clbfDTpW       );

clReleaseMemObject(clbfMCks_f     ); clReleaseMemObject(clbfMCkp2      ); 
clReleaseMemObject(clbfMCkB112    ); clReleaseMemObject(clbfMCkB2f     ); 
clReleaseMemObject(clbfMCkB1f     ); clReleaseMemObject(clbfMCkB2psi   ); 
clReleaseMemObject(clbfMCkB4psi   ); clReleaseMemObject(clbfMCkT1u12_1 ); 
clReleaseMemObject(clbfMCkT1u12_2 ); clReleaseMemObject(clbfMCkAf021_1 ); 
clReleaseMemObject(clbfMCkAf021_2 ); clReleaseMemObject(clbfMCkT1u34_1 ); 
clReleaseMemObject(clbfMCkT1u34_2 ); clReleaseMemObject(clbfMCkApf021_1);
clReleaseMemObject(clbfMCkApf021_2); clReleaseMemObject(clbfMCkAf201_1 ); 
clReleaseMemObject(clbfMCkAf201_2 ); clReleaseMemObject(clbfMCkAf221_1 ); 
clReleaseMemObject(clbfMCkAf221_2 ); clReleaseMemObject(clbfMCkAf222_1 ); 
clReleaseMemObject(clbfMCkAf222_2 ); clReleaseMemObject(clbfMCkAf223_1 ); 
clReleaseMemObject(clbfMCkAf223_2 ); clReleaseMemObject(clbfMCkAf243_1 ); 
clReleaseMemObject(clbfMCkAf243_2 ); clReleaseMemObject(clbfMCkW       );

clReleaseMemObject(clbfMCps_f     ); clReleaseMemObject(clbfMCpp2      ); 
clReleaseMemObject(clbfMCpB112    ); clReleaseMemObject(clbfMCpB2f     ); 
clReleaseMemObject(clbfMCpB1f     ); clReleaseMemObject(clbfMCpB2psi   ); 
clReleaseMemObject(clbfMCpB4psi   ); clReleaseMemObject(clbfMCpT1u12_1 ); 
clReleaseMemObject(clbfMCpT1u12_2 ); clReleaseMemObject(clbfMCpAf021_1 ); 
clReleaseMemObject(clbfMCpAf021_2 ); clReleaseMemObject(clbfMCpT1u34_1 ); 
clReleaseMemObject(clbfMCpT1u34_2 ); clReleaseMemObject(clbfMCpApf021_1);
clReleaseMemObject(clbfMCpApf021_2); clReleaseMemObject(clbfMCpAf201_1 ); 
clReleaseMemObject(clbfMCpAf201_2 ); clReleaseMemObject(clbfMCpAf221_1 ); 
clReleaseMemObject(clbfMCpAf221_2 ); clReleaseMemObject(clbfMCpAf222_1 ); 
clReleaseMemObject(clbfMCpAf222_2 ); clReleaseMemObject(clbfMCpAf223_1 ); 
clReleaseMemObject(clbfMCpAf223_2 ); clReleaseMemObject(clbfMCpAf243_1 ); 
clReleaseMemObject(clbfMCpAf243_2 ); clReleaseMemObject(clbfMCpW       );


  clReleaseKernel(kernel);
  clReleaseProgram(program);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);
  cout<<"[PWA]>>>>>>>>>>>>>>>>>CL_Releasing Something is over......................"<<endl;
//  RooFitResult* res = simPdf.fitTo(combdata,Save(),RooFit::NumCPU(6), RooFit::Optimize(0));

  //RooFitResult* res = pdfpipi.fitTo(*datapipi,Save(),RooFit::NumCPU(6));
  //RooFitResult* res = pdfkaka.fitTo(*datakaka,Save(),RooFit::NumCPU(6));

//  res->Print("V");
   
//  RooArgList cpar = res->constPars();
//  RooArgList fpar = res->floatParsFinal();

//  pdfpipi.project(projectfilepipi);
//  pdfkaka.project(projectfilekaka);




cout<<"123456789000000000000"<<endl;
         return 0;
}
void convertToString(const char* filename, std::string& s)
{
        size_t size;
        char* str;
        std::fstream f(filename, (std::fstream::in | std::fstream::binary));
        if (f.is_open()) {
                size_t filesize;
                f.seekg(0, std::fstream::end);
                size = filesize = (size_t)f.tellg();
                f.seekg(0, std::fstream::beg);
                str = new char[size + 1];
                if (!str) {
                        f.close();
                        return ;
                }
                f.read(str, filesize);
                f.close();
                str[size] = '\0';
                s = str;
                delete[] str;
                return ;
        }
        std::cout << "Error: Failed to open file " << s << std::endl;
        return ;
}
