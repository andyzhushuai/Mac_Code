#/usr/bin/python
# coding=utf-8

#USER: Andy Zhu
#LANG: py
#TASK: somescript
#统计sys.stdin中单词数的简单脚本

import sys
text = sys.stdin.read()
words = text.split()
wordcount = len(words)
print 'Wordcount: ', wordcount
