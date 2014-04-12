#/usr/bin/python
# coding=utf-8

#USER: Andy Zhu
#LANG: py
#TASK: code

import web

urls = (
		'/(.*)','hello'
		)
class hello:
	def GET(self, name):
		i = web.input(times = 1)
		if not name: name = 'world'
		for c in xrange(int(i.times)): a = 'Hello,', name+'!', return a 

if __name__ == "__main__":
#	web.run(urls, globals())
	app = web.application(urls, globals())
	app.run()
