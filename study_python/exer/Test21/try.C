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
//    pdfpipi.addResonance("R19501","R1950pipi",spin1950pp1,m1950,w1950,rho1950pp1,phi1950pp1,proT1950pp1);//04  //11

////**************  f0(1950) 2+ 2 pp
  RooRealVar spin1950pp2("spin1950pp2","spin1950pp2", 22);
  RooRealVar rho1950pp2("rho1950pp2","rho1950pp2", 7.5520,-100.,100.0);
  RooRealVar phi1950pp2("phi1950pp2","phi1950pp2", -0.1037,-3*pi,3*pi);
  RooRealVar proT1950pp2("proT1950pp2","proT1950pp2", 6);
  spin1950pp2.setConstant();
  proT1950pp2.setConstant();
//  rho1950pp2.setConstant();
//  phi1950pp2.setConstant();
//    pdfpipi.addResonance("R19502","R1950pipi",spin1950pp2,m1950,w1950,rho1950pp2,phi1950pp2,proT1950pp2);//04  //12

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
  
  cout<<"-----------------"<<endl;
  RooDataSet *data22 = RooDataSet::read(indatakaka,theSet);
  data22->Print();
  RooDataSet *datakaka= new RooDataSet(data22->GetName(),data22->GetTitle(),data22,*data22->get(),0,weight.GetName());
  datakaka->Print();
  cout<<"hello1"<<endl;
  DPFPWAPdf pdfkaka("pdfkaka","pdfkaka",v11,v12,v13,v14,v21,v22,v23,v24,v31,v32,v33,v34,v41,v42,v43,v44,&dphikaka);

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
