#/usr/bin/python
# coding=utf-8

#USER: Andy Zhu
#LANG: py
#TASK: l11_402

f = open(r'./l11_4.txt')
lines = f.readlines()
f.close()
lines[1] = "isn't a\n"
f = open(r'./l11_4.txt', 'w')
f.writelines(lines)
f.close()

