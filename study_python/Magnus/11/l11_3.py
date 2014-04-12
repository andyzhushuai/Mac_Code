#/usr/bin/python
# coding=utf-8

#USER: Andy Zhu
#LANG: py
#TASK: l11_3

f = open(r'./l11_3.txt')
print f.read(7)
print f.read(4)
f.close()

f = open(r'./l11_3.txt')
print f.read()
f.close()

f = open(r'./l11_3.txt')
for i in range(3):
	print str(i) + ': ' + f.readline(),
f.close()
