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
