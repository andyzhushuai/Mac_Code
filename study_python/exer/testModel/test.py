#/usr/bin/python
# coding=utf-8

#USER: Andy Zhu
#LANG: py
#TASK: test

f01 = open(r'./CPU_MC_Plot/fit/tryModel.C')
lines = f01.readlines()
f01.close()
print lines[75]
f02 = open(r'./pdfkaka.C')
lines[76:76] = f02.readlines()
f02.close()
f03 = open(r'./CPU_MC_Plot/fit/try.C', 'w')
f03.writelines(lines)
f03.close()

print lines[64]
f04 = open(r'./pdfpipi.C')
lines[65:65] = f04.readlines()
f04.close()
f05 = open(r'./CPU_MC_Plot/fit/try.C', 'w')
f05.writelines(lines)
f05.close()

f01 = open(r'./my_Pwa_test10/tryModel.C')
lines = f01.readlines()
f01.close()
print lines[684]
f02 = open(r'./pdfkaka.C')
lines[685:685] = f02.readlines()
f02.close()
f03 = open(r'./my_Pwa_test10/try.C', 'w')
f03.writelines(lines)
f03.close()

print lines[671]
f04 = open(r'./pdfpipi.C')
lines[672:672] = f04.readlines()
f04.close()
f05 = open(r'./my_Pwa_test10/try.C', 'w')
f05.writelines(lines)
f05.close()
