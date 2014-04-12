{
   gSystem->Load("libRooFit");
   gSystem->Load("libPhysics");
   gSystem->Load("../tmp/libDPF.so");
   using namespace RooFit;
  double mjpsi=3.097,mka=0.493677,mpi=0.13957;
  double pi=3.1415926;
  double high=mjpsi;
  double low=0-high;
  double Nreal=50000;
  DPFPWAPoint dphipipi(mka,mka, mpi, mpi, mjpsi, "../../my_Pwa_test10/new_phspdatapipi.dat");
  DPFPWAPoint dphikaka(mka,mka, mka, mka, mjpsi, "../../my_Pwa_test10/new_phspdatakaka.dat");
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











  TString indata,bkgdata;
  TString outfitpipi="outpipi.rep";
  TString outfit="outkk.rep";
  indatapipi="../../Tensor05/fit/phipipi.dat";
  indatakaka="../../Tensor05/fit/phikaka.dat";
  TString projectfilepipi="resultpipi.root";
  TString projectfilekaka="resultkaka.root";
  bkgdata="kstarkp.dat";

  RooArgSet theSet1,theSet2,theSet3;
  theSet1.add(RooArgSet(v11,v12,v13,v14,v21,v22,v23,v24));
  theSet2.add(RooArgSet(v31,v32,v33,v34,v41,v42,v43,v44));
  theSet3.add(RooArgSet(weight));
  RooArgSet theSet4(theSet1,theSet2,"");
  RooArgSet theSet(theSet4,theSet3,"");

  cout<<"-----------------"<<endl;
  RooDataSet *data11 = RooDataSet::read(indatapipi,theSet);
  data11->Print();
  RooDataSet *datapipi= new RooDataSet(data11->GetName(),data11->GetTitle(),data11,*data11->get(),0,weight.GetName());
  datapipi->Print();
  cout<<"hello1"<<endl;
  DPFPWAPdf pdfpipi("pdfpipi","pdfpipi",v11,v12,v13,v14,v21,v22,v23,v24,v31,v32,v33,v34,v41,v42,v43,v44,&dphipipi);

	/*****************************Adding pdfpipi begin***********************************/
	/*****************************Adding pdfpipi end  ***********************************/
  
  cout<<"-----------------"<<endl;
  RooDataSet *data22 = RooDataSet::read(indatakaka,theSet);
  data22->Print();
  RooDataSet *datakaka= new RooDataSet(data22->GetName(),data22->GetTitle(),data22,*data22->get(),0,weight.GetName());
  datakaka->Print();
  cout<<"hello1"<<endl;
  DPFPWAPdf pdfkaka("pdfkaka","pdfkaka",v11,v12,v13,v14,v21,v22,v23,v24,v31,v32,v33,v34,v41,v42,v43,v44,&dphikaka);

	/*****************************Adding pdfkaka begin***********************************/
	/*****************************Adding pdfkaka end  ***********************************/

 

  TStopwatch timer;
  timer.Start();

  RooCategory kapi("kapi","kapi");
  kapi.defineType("phipipi");
  kapi.defineType("phikaka");
  
  RooDataSet combdata("combdata","combined data",theSet, Index(kapi),Import("phipipi",*datapipi),Import("phikaka",*datakaka));

  RooSimultaneous simPdf("simPdf","simultaneous pdf",kapi);
  simPdf.addPdf(pdfpipi,"phipipi");
  simPdf.addPdf(pdfkaka,"phikaka");
  
//  RooFitResult* res = simPdf.fitTo(combdata,Save(),RooFit::NumCPU(6), RooFit::Optimize(0));
  //RooFitResult* res = pdfpipi.fitTo(*datapipi,Save(),RooFit::NumCPU(6));
  //RooFitResult* res = pdfkaka.fitTo(*datakaka,Save(),RooFit::NumCPU(6));
   TFile fr("../../my_Pwa_test10/fitresult.root");
   RooFitResult* resSim = (RooFitResult*)fr.Get("fitresult");
   resSim->Print("V");
//	 Int_t istat = result->covQual();
	 cout<<"**********************************"<<endl;
	 cout<<"*"<<"  Status: "<<resSim->covQual()<<endl;
	 cout<<"*"<<endl;
	 cout<<"**********************************"<<endl;
   fr.Close();

  RooArgList cpar = resSim->constPars();
  RooArgList fpar = resSim->floatParsFinal();

  ///////////////save changed pars
  TIterator* parIterpipi =fpar.createIterator() ;
  RooRealVar *parpipi(0);
  parIterpipi->Reset();
  ofstream paramoutpipi("paraF.rep");
  while(0 != (parpipi= (RooRealVar*)parIterpipi->Next())) { //changed pars are putted out to para1.rep.
  paramoutpipi<<parpipi->GetName()<<"  "<<parpipi->getVal()<<"  "<<parpipi->getError()<<endl;
  }
  paramoutpipi.close();

  TIterator* parIterpipiC =cpar.createIterator() ;
  RooRealVar *parpipiC(0);
  parIterpipiC->Reset();
  ofstream paramoutpipiC("paraC.rep");
  while(0 != (parpipiC= (RooRealVar*)parIterpipiC->Next())) { //changed pars are putted out to para1.rep.
  paramoutpipiC<<parpipiC->GetName()<<"  "<<parpipiC->getVal()<<"  "<<parpipiC->getError()<<endl;
  }
  paramoutpipiC.close();

  timer.Stop();
  cout<<"Fit time:"<<timer.CpuTime()<<endl;
 // res->Print("V");
   
//  RooArgList cpar = res->constPars();
//  RooArgList fpar = res->floatParsFinal();

  pdfpipi.project(fpar, projectfilepipi, "../../Tensor05/fit/tens_PHSPpp.dat");
  pdfkaka.project(fpar, projectfilekaka, "../../Tensor05/fit/tens_PHSPkk.dat");
//  pdfpipi.project(projectfilepipi, fpar, "./tens_PHSPphipipi.dat");
//  pdfkaka.project(projectfilekaka, fpar, "./tens_PHSPphikaka.dat");

//
cout<<"123456789000000000000"<<endl;
}
