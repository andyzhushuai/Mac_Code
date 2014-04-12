class Animal(object):
	def run(self):
		print 'Animal is running...'

class Dog(Animal):
	def run(self):
		print 'Dog is running...'

class Cat(Animal):
	def run(self):
		print 'Cat is running...'
	pass

dog = Dog()
dog.run()

cat = Cat()
cat.run()

