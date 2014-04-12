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
////****************  f0(980) 0+ 1 pp
  RooRealVar m980("m980","m980", 0.9650, 0.900, 1.00);
  RooRealVar g10("g10","g10", 0.1650,0.100,0.500);
  RooRealVar g20("g20","g20", 0.6950,0.100,1.500);
  RooRealVar spin980pp1("spin980pp1","spin980pp1", 1);
  RooRealVar rho980pp1("rho980pp1","rho980pp1", 25.4288,-100.,100.0);
  RooRealVar phi980pp1("phi980pp1","phi980pp1", 4.6788,-2*pi,2*pi);
  RooRealVar proT980pp1("proT980pp1","proT980pp1", 2);
  m980.setConstant();
  spin980pp1.setConstant();
  proT980pp1.setConstant();
  g10.setConstant();
  g20.setConstant();
//  rho980pp1.setConstant();// BC
//  phi980pp1.setConstant();// BC
    pdfpipi.addResonance980("R9801","R980pipi",spin980pp1,m980,g10,g20,rho980pp1,phi980pp1,proT980pp1);//02  //01

////****************  f0(980) 0+ 2 pp
  RooRealVar spin980pp2("spin980pp2","spin980pp2", 2);
  RooRealVar rho980pp2("rho980pp2","rho980pp2", 8.0024,-100.,100.0);
  RooRealVar phi980pp2("phi980pp2","phi980pp2", 4.3268,-2*pi,2*pi);
  RooRealVar proT980pp2("proT980pp2","proT980pp2", 2);
  spin980pp2.setConstant();
  proT980pp2.setConstant();
//  rho980pp2.setConstant();// BC
//  phi980pp2.setConstant();// BC
    pdfpipi.addResonance980("R9802","R980pipi",spin980pp2,m980,g10,g20,rho980pp2,phi980pp2,proT980pp2);//02  //02

////****************  f0(1370) 0+ 1 pp
  RooRealVar m1370("m1370","m1370", 1.350, 1.200, 1.500);
  RooRealVar w1370("w1370","w1370", 0.265,0.2,0.5);
  RooRealVar spin1370pp1("spin1370pp1","spin1370pp1", 1);
  RooRealVar rho1370pp1("rho1370pp1","rho1370pp1", 65.8879,-100.0,100.0);
  RooRealVar phi1370pp1("phi1370pp1","phi1370pp1", 0.4468,-pi,pi);
  RooRealVar proT1370pp1("proT1370pp1","proT1370pp1", 1);
  spin1370pp1.setConstant();
  proT1370pp1.setConstant();
  m1370.setConstant();
  w1370.setConstant();
//  rho1370pp1.setConstant();
//  phi1370pp1.setConstant();
    pdfpipi.addResonance("R13701","R1370pipi",spin1370pp1,m1370,w1370,rho1370pp1,phi1370pp1,proT1370pp1);//04  //03

////**************  f0(1370) 0+ 2 pp
  RooRealVar spin1370pp2("spin1370pp2","spin1370pp2", 2);
  RooRealVar rho1370pp2("rho1370pp2","rho1370pp2", 16.1689,-100.0,100.0);
  RooRealVar phi1370pp2("phi1370pp2","phi1370pp2", 0.7596,-pi,pi);
  RooRealVar proT1370pp2("proT1370pp2","proT1370pp2", 1);
  spin1370pp2.setConstant();
  proT1370pp2.setConstant();
//  rho1370pp2.setConstant();
//  phi1370pp2.setConstant();
    pdfpipi.addResonance("R13702","R1370pipi",spin1370pp2,m1370,w1370,rho1370pp2,phi1370pp2,proT1370pp2);//04  //04

////**************  f0(1790) 0+ 1 pp
  RooRealVar m1790("m1790","m1790", 1.7900, 1.70, 1.90);
  RooRealVar w1790("w1790","w1790", 0.2700,0.150,0.350);
  RooRealVar spin1790pp1("spin1790pp1","spin1790pp1", 1);
  RooRealVar rho1790pp1("rho1790pp1","rho1790pp1", 69.9798,-100.0,100.0);
  RooRealVar phi1790pp1("phi1790pp1","phi1790pp1", 0.5430,-pi,pi);
  RooRealVar proT1790pp1("proT1790pp1","proT1790pp1", 1);
  spin1790pp1.setConstant();
  proT1790pp1.setConstant();
  m1790.setConstant();//O BC
  w1790.setConstant();//O BC
//  rho1790pp1.setConstant();//O BC
//  phi1790pp1.setConstant();//open BC
    pdfpipi.addResonance("R17901","R1790pipi",spin1790pp1,m1790,w1790,rho1790pp1,phi1790pp1,proT1790pp1);//04  //05

////**************  f0(1790) 0+ 2 pp
  RooRealVar spin1790pp2("spin1790pp2","spin1790pp2", 2);
  RooRealVar rho1790pp2("rho1790pp2","rho1790pp2", 39.7695,-100.0,100.0);
  RooRealVar phi1790pp2("phi1790pp2","phi1790pp2", -0.3770,-pi,pi);
  RooRealVar proT1790pp2("proT1790pp2","proT1790pp2", 1);
  spin1790pp2.setConstant();
  proT1790pp2.setConstant();
//  rho1790pp2.setConstant();//O BC
//  phi1790pp2.setConstant();//O BC
    pdfpipi.addResonance("R17902","R1790pipi",spin1790pp2,m1790,w1790,rho1790pp2,phi1790pp2,proT1790pp2);//04  //06

////**************  f0(sigma600) 0+ 1 pp
  RooRealVar m600("m600","m600", 0.9264, 0.800, 1.00);
  RooRealVar spin600pp1("spin600pp1","spin600pp1", 1);
  RooRealVar b600pp11("b600pp11","b600pp11", 0.5843,0.500,0.600);
  RooRealVar b600pp12("b600pp12","b600pp12", 1.6663,1.500,1.7000);
  RooRealVar b600pp13("b600pp13","b600pp13", 1.0820,0.800,1.500);
  RooRealVar b600pp14("b600pp14","b600pp14", 0.0024,0.0010,0.0050);
  RooRealVar b600pp15("b600pp15","b600pp15", 1.0000,0.5000,1.500);
  RooRealVar rho600pp1("rho600pp1","rho600pp1", 34.8889,-100.0,100.0);
  RooRealVar phi600pp1("phi600pp1","phi600pp1", 1.8491,-pi,pi);
  RooRealVar proT600pp1("proT600pp1","proT600pp1", 3);
  m600.setConstant();
  proT600pp1.setConstant();
  b600pp11.setConstant();
  b600pp12.setConstant();
  b600pp13.setConstant();
  b600pp14.setConstant();
  b600pp15.setConstant();
  spin600pp1.setConstant();
//  rho600pp1.setConstant();
//  phi600pp1.setConstant();
    pdfpipi.addResonance600("R6001","R600pipi",spin600pp1,m600,b600pp11,b600pp12,b600pp13,b600pp14,b600pp15,rho600pp1,phi600pp1,proT600pp1);//0107

////**************  f0(sigma600) 0+ 2 pp
  RooRealVar spin600pp2("spin600pp2","spin600pp2", 2);
  RooRealVar b600pp21("b600pp21","b600pp21", 0.5843,0.200,0.900);
  RooRealVar b600pp22("b600pp22","b600pp22", 1.6663,1.00,1.9000);
  RooRealVar b600pp23("b600pp23","b600pp23", 1.0820,0.800,1.500);
  RooRealVar b600pp24("b600pp24","b600pp24", 0.0024,0.0010,0.0050);
  RooRealVar b600pp25("b600pp25","b600pp25", 1.0000,0.5000,1.500);
  RooRealVar rho600pp2("rho600pp2","rho600pp2", 13.1566,-100.0,100.0);
  RooRealVar phi600pp2("phi600pp2","phi600pp2", 1.9269,-pi,pi);
  RooRealVar proT600pp2("proT600pp2","proT600pp2", 3);
  spin600pp2.setConstant();
  proT600pp2.setConstant();
  b600pp21.setConstant();
  b600pp22.setConstant();
  b600pp23.setConstant();
  b600pp24.setConstant();
  b600pp25.setConstant();
//  rho600pp2.setConstant();
//  phi600pp2.setConstant();
    pdfpipi.addResonance600("R6002","R600pipi",spin600pp2,m600,b600pp21,b600pp22,b600pp23,b600pp24,b600pp25,rho600pp2,phi600pp2,proT600pp2);//0108

////**************  f0(1500) 0+ 1 pp
  RooRealVar m1500("m1500","m1500", 1.4950, 1.00, 1.90);
  RooRealVar w1500("w1500","w1500", 0.1220,0.100,0.150);
  RooRealVar spin1500pp1("spin1500pp1","spin1500pp1", 1);
  RooRealVar rho1500pp1("rho1500pp1","rho1500pp1", 53.6250,-100.0,100.0);
  RooRealVar phi1500pp1("phi1500pp1","phi1500pp1", 2.7549,-pi,pi);
  RooRealVar proT1500pp1("proT1500pp1","proT1500pp1", 1);
  spin1500pp1.setConstant();
  proT1500pp1.setConstant();
  m1500.setConstant();
  w1500.setConstant();
//  rho1500pp1.setConstant();
//  phi1500pp1.setConstant();
    pdfpipi.addResonance("R15001","R1500pipi",spin1500pp1,m1500,w1500,rho1500pp1,phi1500pp1,proT1500pp1);//04  //09

////**************  f0(1500) 0+ 2 pp
  RooRealVar spin1500pp2("spin1500pp2","spin1500pp2", 2);
  RooRealVar rho1500pp2("rho1500pp2","rho1500pp2", 23.4287,-100.0,100.0);
  RooRealVar phi1500pp2("phi1500pp2","phi1500pp2", 2.5820,-pi,pi);
  RooRealVar proT1500pp2("proT1500pp2","proT1500pp2", 1);
  spin1500pp2.setConstant();
  proT1500pp2.setConstant();
//  rho1500pp2.setConstant();
//  phi1500pp2.setConstant();
    pdfpipi.addResonance("R15002","R1500pipi",spin1500pp2,m1500,w1500,rho1500pp2,phi1500pp2,proT1500pp2);//04  //10

////**************  f0(1270) 2+ 1 pp
  RooRealVar spin1270pp11("spin1270pp11","spin1270pp11", 21);
  RooRealVar m1270("m1270","m1270", 1.2750, 1.0, 1.800);
  RooRealVar w1270("w1270","w1270", 0.1900,0.10,0.90);
  RooRealVar rho1270pp11("rho1270pp11","rho1270pp11", 23.4619,-100.0,100.0);
  RooRealVar phi1270pp11("phi1270pp11","phi1270pp11", 0.6866,-2*pi,2*pi);
  RooRealVar proT1270pp11("proT1270pp11","proT1270pp11", 6);
  spin1270pp11.setConstant();
  proT1270pp11.setConstant();
//  m1270.setConstant();
//  w1270.setConstant();
//  rho1270pp11.setConstant();
//  phi1270pp11.setConstant();
    pdfpipi.addResonance("R12701","R1270pipi",spin1270pp11,m1270,w1270,rho1270pp11,phi1270pp11,proT1270pp11);//04  //11

////**************  f0(1270) 2+ 2 pp
  RooRealVar spin1270pp12("spin1270pp12","spin1270pp12", 22);
  RooRealVar rho1270pp12("rho1270pp12","rho1270pp12", 7.5520,-100.,100.0);
  RooRealVar phi1270pp12("phi1270pp12","phi1270pp12", -0.1037,-2*pi,2*pi);
  RooRealVar proT1270pp12("proT1270pp12","proT1270pp12", 6);
  spin1270pp12.setConstant();
  proT1270pp12.setConstant();
//  rho1270pp12.setConstant();
//  phi1270pp12.setConstant();
    pdfpipi.addResonance("R12702","R1270pipi",spin1270pp12,m1270,w1270,rho1270pp12,phi1270pp12,proT1270pp12);//04  //12

////**************  f0(1270) 2+ 3 pp
  RooRealVar spin1270pp13("spin1270pp13","spin1270pp13", 23);
  RooRealVar rho1270pp13("rho1270pp13","rho1270pp13", 5.3346,-100.,100.0);
  RooRealVar phi1270pp13("phi1270pp13","phi1270pp13", -0.0750,-2*pi,2*pi);
  RooRealVar proT1270pp13("proT1270pp13","proT1270pp13", 6);
  spin1270pp13.setConstant();
  proT1270pp13.setConstant();
//  rho1270pp13.setConstant();
//  phi1270pp13.setConstant();
    pdfpipi.addResonance("R12703","R1270pipi",spin1270pp13,m1270,w1270,rho1270pp13,phi1270pp13,proT1270pp13);//04  //13
  
////**************  f0(1270) 2+ 4 pp
  RooRealVar spin1270pp14("spin1270pp14","spin1270pp14", 24);
  RooRealVar rho1270pp14("rho1270pp14","rho1270pp14", 4.3929,-100.,100.0);
  RooRealVar phi1270pp14("phi1270pp14","phi1270pp14", 3.2811,-2*pi,2*pi);
  RooRealVar proT1270pp14("proT1270pp14","proT1270pp14", 6);
  spin1270pp14.setConstant();
  proT1270pp14.setConstant();
//  rho1270pp14.setConstant();
//  phi1270pp14.setConstant();
  pdfpipi.addResonance("R12704","R1270pipi",spin1270pp14,m1270,w1270,rho1270pp14,phi1270pp14,proT1270pp14);//04  //14

////**************  f0(1270) 2+ 5 pp
  RooRealVar spin1270pp15("spin1270pp15","spin1270pp15", 25);
  RooRealVar rho1270pp15("rho1270pp15","rho1270pp15", 4.3929,-100.,100.0);
  RooRealVar phi1270pp15("phi1270pp15","phi1270pp15", 3.2811,-2*pi,2*pi);
  RooRealVar proT1270pp15("proT1270pp15","proT1270pp15", 6);
  spin1270pp15.setConstant();
  proT1270pp15.setConstant();
//  rho1270pp15.setConstant();
//  phi1270pp15.setConstant();
//  pdfpipi.addResonance("R12705","R1270pipi",spin1270pp15,m1270,w1270,rho1270pp15,phi1270pp15,proT1270pp15);//04  //14

////**************  f0(1950) 2+ 1 pp
  RooRealVar m1950("m1950","m1950", 1.9440, 1.0, 2.200);
  RooRealVar w1950("w1950","w1950", 0.4720,0.10,0.90);
  RooRealVar spin1950pp1("spin1950pp1","spin1950pp1", 21);
  RooRealVar rho1950pp1("rho1950pp1","rho1950pp1", 23.4619,-100.0,100.0);
  RooRealVar phi1950pp1("phi1950pp1","phi1950pp1", 0.6866,-3*pi,3*pi);
  RooRealVar proT1950pp1("proT1950pp1","proT1950pp1", 6);
//  m1950.setConstant();
//  w1950.setConstant();
  spin1950pp1.setConstant();
  proT1950pp1.setConstant();
//  rho1950pp1.setConstant();
//  phi1950pp1.setConstant();
//  pdfpipi.addResonance("R19501","R1950pipi",spin1950pp1,m1950,w1950,rho1950pp1,phi1950pp1,proT1950pp1);//04  //11

////**************  f0(1950) 2+ 2 pp
  RooRealVar spin1950pp2("spin1950pp2","spin1950pp2", 22);
  RooRealVar rho1950pp2("rho1950pp2","rho1950pp2", 7.5520,-100.,100.0);
  RooRealVar phi1950pp2("phi1950pp2","phi1950pp2", -0.1037,-3*pi,3*pi);
  RooRealVar proT1950pp2("proT1950pp2","proT1950pp2", 6);
  spin1950pp2.setConstant();
  proT1950pp2.setConstant();
//  rho1950pp2.setConstant();
//  phi1950pp2.setConstant();
//  pdfpipi.addResonance("R19502","R1950pipi",spin1950pp2,m1950,w1950,rho1950pp2,phi1950pp2,proT1950pp2);//04  //12

////**************  f0(1950) 2+ 3 pp
  RooRealVar spin1950pp3("spin1950pp3","spin1950pp3", 23);
  RooRealVar rho1950pp3("rho1950pp3","rho1950pp3", 5.3346,-100.,100.0);
  RooRealVar phi1950pp3("phi1950pp3","phi1950pp3", -0.0750,-3*pi,3*pi);
  RooRealVar proT1950pp3("proT1950pp3","proT1950pp3", 6);
  spin1950pp3.setConstant();
  proT1950pp3.setConstant();
//  rho1950pp3.setConstant();
//  phi1950pp3.setConstant();
//  pdfpipi.addResonance("R19503","R1950pipi",spin1950pp3,m1950,w1950,rho1950pp3,phi1950pp3,proT1950pp3);//04  //13
  
////**************  f0(1950) 2+ 4 pp
  RooRealVar spin1950pp4("spin1950pp4","spin1950pp4", 24);
  RooRealVar rho1950pp4("rho1950pp4","rho1950pp4", 4.3929,-100.,100.0);
  RooRealVar phi1950pp4("phi1950pp4","phi1950pp4", 3.2811,-3*pi,3*pi);
  RooRealVar proT1950pp4("proT1950pp4","proT1950pp4", 6);
  spin1950pp4.setConstant();
  proT1950pp4.setConstant();
//  rho1950pp4.setConstant();
//  phi1950pp4.setConstant();
//  pdfpipi.addResonance("R19504","R1950pipi",spin1950pp4,m1950,w1950,rho1950pp4,phi1950pp4,proT1950pp4);//04  //14

////**************  f0(1950) 2+ 5 pp
  RooRealVar spin1950pp5("spin1950pp5","spin1950pp5", 25);
  RooRealVar rho1950pp5("rho1950pp5","rho1950pp5", 4.3929,-100.,100.0);
  RooRealVar phi1950pp5("phi1950pp5","phi1950pp5", 3.2811,-3*pi,3*pi);
  RooRealVar proT1950pp5("proT1950pp5","proT1950pp5", 6);
  spin1950pp5.setConstant();
  proT1950pp5.setConstant();
//  rho1950pp5.setConstant();
//  phi1950pp5.setConstant();
//  pdfpipi.addResonance("R19505","R1950pipi",spin1950pp5,m1950,w1950,rho1950pp5,phi1950pp5,proT1950pp5);//04  //15

  PWASingNLL::setpdfpi(&pdfpipi);
  
  cout<<"-----------------"<<endl;
  RooDataSet *data22 = RooDataSet::read(indatakaka,theSetd);
  data22->Print();
  RooDataSet *datakaka= new RooDataSet(data22->GetName(),data22->GetTitle(),data22,*data22->get(),0,weight.GetName());
  datakaka->Print();

  PWAPdf pdfkaka("pdfkaka","pdfkaka",v11,v12,v13,v14,v21,v22,v23,v24,v31,v32,v33,v34,v41,v42,v43,v44,&dphikaka);

////**************  f0(980) 0+ 1 kk 
  RooRealVar spin980kk1("spin980kk1","spin980kk1", 1);
  RooRealVar rho980kk1("rho980kk1","rho980kk1", 0.7628,-100.0,100.0);
  RooRealVar phi980kk1("phi980kk1","phi980kk1", 1.2817,-pi,pi);
  RooRealVar proT980kk1("proT980kk1","proT980kk1", 2);
  spin980kk1.setConstant();
  proT980kk1.setConstant();
//  rho980kk1.setConstant();// BC
//  phi980kk1.setConstant();// BC
    pdfkaka.addResonance980("R9801","R980kk",spin980kk1,m980,g10,g20,rho980kk1,phi980kk1,proT980kk1);//02  //01

////**************  f0(980) 0+ 2 kk 
  RooRealVar spin980kk2("spin980kk2","spin980kk2", 2);
  RooRealVar rho980kk2("rho980kk2","rho980kk2", 0.2400,-100.0,100.0);
  RooRealVar phi980kk2("phi980kk2","phi980kk2", 1.0694,-pi,pi);
  RooRealVar proT980kk2("proT980kk2","proT980kk2", 2);
  spin980kk2.setConstant();
  proT980kk2.setConstant();
//  rho980kk2.setConstant();// BC
//  phi980kk2.setConstant();// BC
    pdfkaka.addResonance980("R9802","R980kk",spin980kk2,m980,g10,g20,rho980kk2,phi980kk2,proT980kk2);//02  //02

////**************  f0(1370) 0+ 1 kk
  RooRealVar spin1370kk1("spin1370kk1","spin1370kk1", 1);
  RooRealVar rho1370kk1("rho1370kk1","rho1370kk1", 0.3360,-100.0,100.0);
  RooRealVar phi1370kk1("phi1370kk1","phi1370kk1", 3.3365,-2*pi,2*pi);
  RooRealVar proT1370kk1("proT1370kk1","proT1370kk1", 1);
  spin1370kk1.setConstant();
  proT1370kk1.setConstant();
//  rho1370kk1.setConstant();
//  phi1370kk1.setConstant();
    pdfkaka.addResonance("R13701","R1370kk",spin1370kk1,m1370,w1370,rho1370kk1,phi1370kk1,proT1370kk1);//04  //03

////***************  f0(1370) 0+ 2 kk
  RooRealVar spin1370kk2("spin1370kk2","spin1370kk2", 2);
  RooRealVar rho1370kk2("rho1370kk2","rho1370kk2", 0.08246,-100.0,100.0);
  RooRealVar phi1370kk2("phi1370kk2","phi1370kk2", -2.7921,-pi,pi);
  RooRealVar proT1370kk2("proT1370kk2","proT1370kk2", 1);
  spin1370kk2.setConstant();
  proT1370kk2.setConstant();
//  rho1370kk2.setConstant();
//  phi1370kk2.setConstant();
    pdfkaka.addResonance("R13702","R1370kk",spin1370kk2,m1370,w1370,rho1370kk2,phi1370kk2,proT1370kk2);//04  //04

////***************  f0(1790) 0+ 1 kk 
  RooRealVar spin1790kk1("spin1790kk1","spin1790kk1", 1);
  RooRealVar rho1790kk1("rho1790kk1","rho1790kk1", 0.5598,-100.0,100.0);
  RooRealVar phi1790kk1("phi1790kk1","phi1790kk1", 5.6406,-2*pi,2*pi);
  RooRealVar proT1790kk1("proT1790kk1","proT1790kk1", 1);
  spin1790kk1.setConstant();
  proT1790kk1.setConstant();
//  rho1790kk1.setConstant();//O BC
//  phi1790kk1.setConstant();//open Bc
    pdfkaka.addResonance("R17901","R1790kk",spin1790kk1,m1790,w1790,rho1790kk1,phi1790kk1,proT1790kk1);//04  //05

////***************  f0(1790) 0+ 2 kk
  RooRealVar spin1790kk2("spin1790kk2","spin1790kk2", 2);
  RooRealVar rho1790kk2("rho1790kk2","rho1790kk2", 0.3181,-100.0,100.0);
  RooRealVar phi1790kk2("phi1790kk2","phi1790kk2", 4.2865,-2*pi,2*pi);
  RooRealVar proT1790kk2("proT1790kk2","proT1790kk2", 1);
  spin1790kk2.setConstant();
  proT1790kk2.setConstant();
//  rho1790kk2.setConstant();//O BC
//  phi1790kk2.setConstant();//open BC
    pdfkaka.addResonance("R17902","R1790kk",spin1790kk2,m1790,w1790,rho1790kk2,phi1790kk2,proT1790kk2);//04  //06

////***************  f0(600) 0+ 1 kk
  RooRealVar spin600kk1("spin600kk1","spin600kk1", 1);
  RooRealVar b600kk11("b600kk11","b600kk11", 0.5843,0.10,0.90);
  RooRealVar b600kk12("b600kk12","b600kk12", 1.6663,1.0,2.50);
  RooRealVar b600kk13("b600kk13","b600kk13", 1.0820,0.500,1.500);
  RooRealVar b600kk14("b600kk14","b600kk14", 0.0024,0.0010,0.0080);
  RooRealVar b600kk15("b600kk15","b600kk15", 1.0000,0.500,1.500);
  RooRealVar rho600kk1("rho600kk1","rho600kk1", 0.5477,-100.0,100.0);
  RooRealVar phi600kk1("phi600kk1","phi600kk1", 3.0705,-2*pi,2*pi);
  RooRealVar proT600kk1("proT600kk1","proT600kk1", 3);
  spin600kk1.setConstant();
  proT600kk1.setConstant();
  b600kk11.setConstant();
  b600kk12.setConstant();
  b600kk13.setConstant();
  b600kk14.setConstant();
  b600kk15.setConstant();
//  rho600kk1.setConstant();
//  phi600kk1.setConstant();
    pdfkaka.addResonance600("R6001","R600kk",spin600kk1,m600,b600kk11,b600kk12,b600kk13,b600kk14,b600kk15,rho600kk1,phi600kk1,proT600kk1);//0107

////***************  f0(600) 0+ 2 kk
  RooRealVar spin600kk2("spin600kk2","spin600kk2", 2);
  RooRealVar b600kk21("b600kk21","b600kk21", 0.5843,0.100,1.500);
  RooRealVar b600kk22("b600kk22","b600kk22", 1.6663,0.500,2.7000);
  RooRealVar b600kk23("b600kk23","b600kk23", 1.0820,0.500,1.500);
  RooRealVar b600kk24("b600kk24","b600kk24", 0.0024,0.001,0.0080);
  RooRealVar b600kk25("b600kk25","b600kk25", 1.0000,0.5000,1.500);
  RooRealVar rho600kk2("rho600kk2","rho600kk2", 0.2065,-100.0,100.0);
  RooRealVar phi600kk2("phi600kk2","phi600kk2", 2.1623,-pi,pi);
  RooRealVar proT600kk2("proT600kk2","proT600kk2", 3);
  spin600kk2.setConstant();
  proT600kk2.setConstant();
  b600kk21.setConstant();
  b600kk22.setConstant();
  b600kk23.setConstant();
  b600kk24.setConstant();
  b600kk25.setConstant();
//  rho600kk2.setConstant();
//  phi600kk2.setConstant();
    pdfkaka.addResonance600("R6002","R600kk",spin600kk2,m600,b600kk21,b600kk22,b600kk23,b600kk24,b600kk25,rho600kk2,phi600kk2,proT600kk2);//0108

////***************  f0(1500) 0+ 1 kk 
  RooRealVar spin1500kk1("spin1500kk1","spin1500kk1", 1);
  RooRealVar rho1500kk1("rho1500kk1","rho1500kk1", 0.6166,-100.0,100.0);
  RooRealVar phi1500kk1("phi1500kk1","phi1500kk1", 3.9934,-2*pi,2*pi);//Bes2
  RooRealVar proT1500kk1("proT1500kk1","proT1500kk1", 1);
  spin1500kk1.setConstant();
  proT1500kk1.setConstant();
//  rho1500kk1.setConstant();
//  phi1500kk1.setConstant();
    pdfkaka.addResonance("R15001","R1500kk",spin1500kk1,m1500,w1500,rho1500kk1,phi1500kk1,proT1500kk1);//04  //09

////***************  f0(1500) 0+ 2 kk
  RooRealVar spin1500kk2("spin1500kk2","spin1500kk2", 2);
  RooRealVar rho1500kk2("rho1500kk2","rho1500kk2", 0.2694,-100.0,100.0);
  RooRealVar phi1500kk2("phi1500kk2","phi1500kk2", 4.3124,-2*pi,2*pi);
  RooRealVar proT1500kk2("proT1500kk2","proT1500kk2", 1);
  spin1500kk2.setConstant();
  proT1500kk2.setConstant();
//  rho1500kk2.setConstant();
//  phi1500kk2.setConstant();
    pdfkaka.addResonance("R15002","R1500kk",spin1500kk2,m1500,w1500,rho1500kk2,phi1500kk2,proT1500kk2);//04  //10

////***************  f0(1710) 0+ 1 kk 
  RooRealVar m1710("m1710","m1710", 1.7070, 1.650, 1.800);
  RooRealVar w1710("w1710","w1710", 0.1250,0.10,0.1500);
  RooRealVar spin1710kk1("spin1710kk1","spin1710kk1", 1);
  RooRealVar rho1710kk1("rho1710kk1","rho1710kk1", 1.0527,-100.0,100.0);
  RooRealVar phi1710kk1("phi1710kk1","phi1710kk1", 6.8807,-3*pi,3*pi);
  RooRealVar proT1710kk1("proT1710kk1","proT1710kk1", 1);
  m1710.setConstant();//open (Bes2close)
  w1710.setConstant();//open (Bes2close)
  spin1710kk1.setConstant();
  proT1710kk1.setConstant();
//  rho1710kk1.setConstant();//O BC
//  phi1710kk1.setConstant();//open (Bes2close)
    pdfkaka.addResonance("R17101","R1710kk",spin1710kk1,m1710,w1710,rho1710kk1,phi1710kk1,proT1710kk1);//04  //11

////***************  f0(1710) 0+ 2 kk 
  RooRealVar spin1710kk2("spin1710kk2","spin1710kk2", 2);
  RooRealVar rho1710kk2("rho1710kk2","rho1710kk2", 0.2545,-100.0,100.0);
  RooRealVar phi1710kk2("phi1710kk2","phi1710kk2", -0.0052,-pi,pi);
  RooRealVar proT1710kk2("proT1710kk2","proT1710kk2", 1);
  spin1710kk2.setConstant();
  proT1710kk2.setConstant();
//  rho1710kk2.setConstant();//O BC
//  phi1710kk2.setConstant();//open (Bes2close)
    pdfkaka.addResonance("R17102","R1710kk",spin1710kk2,m1710,w1710,rho1710kk2,phi1710kk2,proT1710kk2);//04  //12

////***************  f0(1270) 2+ 1 kk
  RooRealVar spin1270kk1("spin1270kk1","spin1270kk1", 21);
  RooRealVar rho1270kk1("rho1270kk1","rho1270kk1", 0.1000,-100.0,100.0);
  RooRealVar phi1270kk1("phi1270kk1","phi1270kk1", 2.8428,-2*pi,2*pi);
  RooRealVar proT1270kk1("proT1270kk1","proT1270kk1", 6);
  spin1270kk1.setConstant();
  proT1270kk1.setConstant();
//  rho1270kk1.setConstant();
//  phi1270kk1.setConstant();
    pdfkaka.addResonance("R12701","R1270kk",spin1270kk1,m1270,w1270,rho1270kk1,phi1270kk1,proT1270kk1);//04  //13

////***************  f0(1270) 2+ 2 kk
  RooRealVar spin1270kk2("spin1270kk2","spin1270kk2", 22);
  RooRealVar rho1270kk2("rho1270kk2","rho1270kk2", 0.0322,-100.0,100.0);
  RooRealVar phi1270kk2("phi1270kk2","phi1270kk2", -1.9102,-2*pi,2*pi);
  RooRealVar proT1270kk2("proT1270kk2","proT1270kk2", 6);
  spin1270kk2.setConstant();
  proT1270kk2.setConstant();
//  rho1270kk2.setConstant();
//  phi1270kk2.setConstant();
    pdfkaka.addResonance("R12702","R1270kk",spin1270kk2,m1270,w1270,rho1270kk2,phi1270kk2,proT1270kk2);//04  //14

////***************  f0(1270) 2+ 3 kk
  RooRealVar spin1270kk3("spin1270kk3","spin1270kk3", 23);
  RooRealVar rho1270kk3("rho1270kk3","rho1270kk3", 0.0226,-100.0,100.0);
  RooRealVar phi1270kk3("phi1270kk3","phi1270kk3", 0.3628,-2*pi,2*pi);
  RooRealVar proT1270kk3("proT1270kk3","proT1270kk3", 6);
  spin1270kk3.setConstant();
  proT1270kk3.setConstant();
//  rho1270kk3.setConstant();
//  phi1270kk3.setConstant();
    pdfkaka.addResonance("R12703","R1270kk",spin1270kk3,m1270,w1270,rho1270kk3,phi1270kk3,proT1270kk3);//04  //15

////***************  f0(1270) 2+ 4 kk
  RooRealVar spin1270kk4("spin1270kk4","spin1270kk4", 24);
  RooRealVar rho1270kk4("rho1270kk4","rho1270kk4", 0.0187,-100.0,100.0);
  RooRealVar phi1270kk4("phi1270kk4","phi1270kk4", 1.4555,-2*pi,2*pi);
  RooRealVar proT1270kk4("proT1270kk4","proT1270kk4", 6);
  spin1270kk4.setConstant();
  proT1270kk4.setConstant();
//  rho1270kk4.setConstant();
//  phi1270kk4.setConstant();
    pdfkaka.addResonance("R12704","R1270kk",spin1270kk4,m1270,w1270,rho1270kk4,phi1270kk4,proT1270kk4);//04  //16

////***************  f0(1270) 2+ 5 kk
  RooRealVar spin1270kk5("spin1270kk5","spin1270kk5", 25);
  RooRealVar rho1270kk5("rho1270kk5","rho1270kk5", 0.0000,-100.0,100.0);
  RooRealVar phi1270kk5("phi1270kk5","phi1270kk5", 0.0000,-2*pi,2*pi);
  RooRealVar proT1270kk5("proT1270kk5","proT1270kk5", 6);
  spin1270kk5.setConstant();
  proT1270kk5.setConstant();
//  rho1270kk5.setConstant();
//  phi1270kk5.setConstant();
    pdfkaka.addResonance("R12705","R1270kk",spin1270kk5,m1270,w1270,rho1270kk5,phi1270kk5,proT1270kk5);//04  //17

////***************  f0(1525) 2+ 1 kk
  RooRealVar m1525("m1525","m1525", 1.5210, 0.500, 2.50);
  RooRealVar w1525("w1525","w1525", 0.0770,0.0010,0.800);
  RooRealVar spin1525kk1("spin1525kk1","spin1525kk1", 21);
  RooRealVar rho1525kk1("rho1525kk1","rho1525kk1", 1.0000,-100.0,100.0);
  RooRealVar phi1525kk1("phi1525kk1","phi1525kk1", 0.2000,-2*pi,2*pi);
  RooRealVar proT1525kk1("proT1525kk1","proT1525kk1", 1);
//  m1525.setConstant();
//  w1525.setConstant();
  spin1525kk1.setConstant();
  proT1525kk1.setConstant();
//  rho1525kk1.setConstant();
//  phi1525kk1.setConstant();
    pdfkaka.addResonance("R15251","R1525kk",spin1525kk1,m1525,w1525,rho1525kk1,phi1525kk1,proT1525kk1);//04  //18

////***************  f0(1525) 2+ 2 kk
  RooRealVar spin1525kk2("spin1525kk2","spin1525kk2", 22);
  RooRealVar rho1525kk2("rho1525kk2","rho1525kk2", 0.5878,-100.0,100.0);
  RooRealVar phi1525kk2("phi1525kk2","phi1525kk2", 5.9124,-3*pi,3*pi);
  RooRealVar proT1525kk2("proT1525kk2","proT1525kk2", 1);
  spin1525kk2.setConstant();
  proT1525kk2.setConstant();
//  rho1525kk2.setConstant();
//  phi1525kk2.setConstant();
    pdfkaka.addResonance("R15252","R1525kk",spin1525kk2,m1525,w1525,rho1525kk2,phi1525kk2,proT1525kk2);//04  //19

////***************  f0(1525) 2+ 3 kk
  RooRealVar spin1525kk3("spin1525kk3","spin1525kk3", 23);
  RooRealVar rho1525kk3("rho1525kk3","rho1525kk3", 0.3493,-100.0,100.0);
  RooRealVar phi1525kk3("phi1525kk3","phi1525kk3", 0.1663,-pi,pi);
  RooRealVar proT1525kk3("proT1525kk3","proT1525kk3", 1);
  spin1525kk3.setConstant();
  proT1525kk3.setConstant();
//  rho1525kk3.setConstant();
//  phi1525kk3.setConstant();
    pdfkaka.addResonance("R15253","R1525kk",spin1525kk3,m1525,w1525,rho1525kk3,phi1525kk3,proT1525kk3);//04  //20

////***************  f0(1525) 2+ 4 kk
  RooRealVar spin1525kk4("spin1525kk4","spin1525kk4", 24);
  RooRealVar rho1525kk4("rho1525kk4","rho1525kk4", 0.0000,-100.0,100.0);
  RooRealVar phi1525kk4("phi1525kk4","phi1525kk4", 0.0000,-pi,pi);
  RooRealVar proT1525kk4("proT1525kk4","proT1525kk4", 1);
  spin1525kk4.setConstant();
  proT1525kk4.setConstant();
//  rho1525kk4.setConstant();
//  phi1525kk4.setConstant();
    pdfkaka.addResonance("R15254","R1525kk",spin1525kk4,m1525,w1525,rho1525kk4,phi1525kk4,proT1525kk4);//04  //21

////***************  f0(1525) 2+ 5 kk
  RooRealVar spin1525kk5("spin1525kk5","spin1525kk5", 25);
  RooRealVar rho1525kk5("rho1525kk5","rho1525kk5", 0.0000,-100.0,100.0);
  RooRealVar phi1525kk5("phi1525kk5","phi1525kk5", 0.0000,-pi,pi);
  RooRealVar proT1525kk5("proT1525kk5","proT1525kk5", 1);
  spin1525kk5.setConstant();
  proT1525kk5.setConstant();
//  rho1525kk5.setConstant();
//  phi1525kk5.setConstant();
    pdfkaka.addResonance("R15255","R1525kk",spin1525kk5,m1525,w1525,rho1525kk5,phi1525kk5,proT1525kk5);//04  //22

////***************  f0(1950) 2+ 1 kk
  RooRealVar spin1950kk1("spin1950kk1","spin1950kk1", 21);
  RooRealVar rho1950kk1("rho1950kk1","rho1950kk1", 23.4619,-100.0,100.0);
  RooRealVar phi1950kk1("phi1950kk1","phi1950kk1", 0.6866,-3*pi,3*pi);
  RooRealVar proT1950kk1("proT1950kk1","proT1950kk1", 6);
  spin1950kk1.setConstant();
  proT1950kk1.setConstant();
//  rho1950kk1.setConstant();
//  phi1950kk1.setConstant();
//  pdfkaka.addResonance("R19501","R1950kk",spin1950kk1,m1950,w1950,rho1950kk1,phi1950kk1,proT1950kk1);//04  //18

////***************  f0(1950) 2+ 2 kk
  RooRealVar spin1950kk2("spin1950kk2","spin1950kk2", 22);
  RooRealVar rho1950kk2("rho1950kk2","rho1950kk2", 7.5520,-100.,100.0);
  RooRealVar phi1950kk2("phi1950kk2","phi1950kk2", -0.1037,-3*pi,3*pi);
  RooRealVar proT1950kk2("proT1950kk2","proT1950kk2", 6);
  spin1950kk2.setConstant();
  proT1950kk2.setConstant();
//  rho1950kk2.setConstant();
//  phi1950kk2.setConstant();
//  pdfkaka.addResonance("R19502","R1950kk",spin1950kk2,m1950,w1950,rho1950kk2,phi1950kk2,proT1950kk2);//04  //19

////***************  f0(1950) 2+ 3 kk
  RooRealVar spin1950kk3("spin1950kk3","spin1950kk3", 23);
  RooRealVar rho1950kk3("rho1950kk3","rho1950kk3", 5.3346,-100.,100.0);
  RooRealVar phi1950kk3("phi1950kk3","phi1950kk3", -0.0750,-3*pi,3*pi);
  RooRealVar proT1950kk3("proT1950kk3","proT1950kk3", 6);
  spin1950kk3.setConstant();
  proT1950kk3.setConstant();
//  rho1950kk3.setConstant();
//  phi1950kk3.setConstant();
//  pdfkaka.addResonance("R19503","R1950kk",spin1950kk3,m1950,w1950,rho1950kk3,phi1950kk3,proT1950kk3);//04  //20
  
////***************  f0(1950) 2+ 4 kk
  RooRealVar spin1950kk4("spin1950kk4","spin1950kk4", 24);
  RooRealVar rho1950kk4("rho1950kk4","rho1950kk4", 4.3929,-100.,100.0);
  RooRealVar phi1950kk4("phi1950kk4","phi1950kk4", 3.2811,-3*pi,3*pi);
  RooRealVar proT1950kk4("proT1950kk4","proT1950kk4", 6);
  spin1950kk4.setConstant();
  proT1950kk4.setConstant();
//  rho1950kk4.setConstant();
//  phi1950kk4.setConstant();
//  pdfkaka.addResonance("R19504","R1950kk",spin1950kk4,m1950,w1950,rho1950kk4,phi1950kk4,proT1950kk4);//04  //21

////***************  f0(1950) 2+ 5 kk
  RooRealVar spin1950kk5("spin1950kk5","spin1950kk5", 25);
  RooRealVar rho1950kk5("rho1950kk5","rho1950kk5", 4.3929,-100.,100.0);
  RooRealVar phi1950kk5("phi1950kk5","phi1950kk5", 3.2811,-3*pi,3*pi);
  RooRealVar proT1950kk5("proT1950kk5","proT1950kk5", 6);
  spin1950kk5.setConstant();
  proT1950kk5.setConstant();
//  rho1950kk5.setConstant();
//  phi1950kk5.setConstant();
//  pdfkaka.addResonance("R19505","R1950kk",spin1950kk5,m1950,w1950,rho1950kk5,phi1950kk5,proT1950kk5);//04  //22

////***************  phi(1680) 1- 1 kk
  RooRealVar m1680("m1680","m1680", 1.6150, 0.500, 2.500);
  RooRealVar w1680("w1680","w1680", 0.1300,0.01,0.50);
//  RooRealVar m72980("m72980","m72980", 0.9650, 0.600, 1.200);
  RooRealVar spin1680kk1("spin1680kk1","spin1680kk1", 191);
//  RooRealVar g172("g172","g172", 0.1650,0.01,0.500);
//  RooRealVar g272("g272","g272", 0.6950,0.1,1.0);
  RooRealVar rho1680kk1("rho1680kk1","rho1680kk1", 0.0192,-100.0,100.0);
  RooRealVar phi1680kk1("phi1680kk1","phi1680kk1", -0.5701,-pi,pi);
  RooRealVar proT1680kk1("proT1680kk1","proT1680kk1", 5);
//  m72980.setConstant();
//  g172.setConstant();
//  g272.setConstant();
  m1680.setConstant();
  w1680.setConstant();
  spin1680kk1.setConstant();
  proT1680kk1.setConstant();
//  rho1680kk1.setConstant();
//  phi1680kk1.setConstant();
    pdfkaka.addResonance1680("R16801","R1680kk",spin1680kk1, m1680, m980, w1680, g10, g20,rho1680kk1,phi1680kk1,proT1680kk1);//03  //23

////***************  phi(1680) 1- 2 kk
  RooRealVar spin1680kk2("spin1680kk2","spin1680kk2", 192);
//  RooRealVar m73("m73","m73", 1.6150, 0.500, 2.500);
//  RooRealVar m73980("m73980","m73980", 0.9650, 0.600, 1.200);
//  RooRealVar w73("w73","w73", 0.1300,0.010,0.500);
//  RooRealVar g173("g173","g173", 0.1650,0.010,0.500);
//  RooRealVar g273("g273","g273", 0.6950,0.1,1.0);
  RooRealVar rho1680kk2("rho1680kk2","rho1680kk2", 0.0297,-100.0,100.0);
  RooRealVar phi1680kk2("phi1680kk2","phi1680kk2", 0.1496,-pi,pi);
  RooRealVar proT1680kk2("proT1680kk2","proT1680kk2", 5);
//  m73.setConstant();
//  m73980.setConstant();
//  w73.setConstant();
//  g173.setConstant();
//  g273.setConstant();
  spin1680kk2.setConstant();
  proT1680kk2.setConstant();
//  rho1680kk2.setConstant();
//  phi1680kk2.setConstant();
    pdfkaka.addResonance1680("R16802","R1680kk",spin1680kk2, m1680, m980, w1680, g10, g20,rho1680kk2,phi1680kk2,proT1680kk2);//03  //24

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
