def person(name, age, **kw):
	print 'name:', name, 'age:', age, 'other:', kw

person('Michael', 30)
person('Bob', 35, city='Beijing')
person('Adam', 45, gender='M', job='Engineer')

kw = {'city': 'Beijing', 'jobs': 'Engineer'}
person('Jack', 24, city=kw['city'], jobs=kw['jobs'])
person('Jack', 24, **kw)
