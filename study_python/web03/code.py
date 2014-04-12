#/usr/bin/python
# coding=utf-8

#USER: Andy Zhu
#LANG: py
#TASK: code

import web
render = web.template.render('templates/')

urls = (
	    '/', 'index'
		)

class index:
	def GET(self):
#		return "Hello, world!"
		name = 'Bob'
		return render.index(name)

if __name__ == "__main__":
	app = web.application(urls, globals())
	app.run()

