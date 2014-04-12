#/usr/bin/python
# coding=utf-8

#USER: Andy Zhu
#LANG: py
#TASK: l2_2

# 对http://www.something.com形式的URL进行分割

url = raw_input('Please enter the URL: ')
domain01 = url[11:-4]
domain02 = url[7:]

print "Domain name: " + domain01
print "Total  name: " + domain02

