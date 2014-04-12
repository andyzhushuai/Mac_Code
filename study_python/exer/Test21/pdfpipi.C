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
