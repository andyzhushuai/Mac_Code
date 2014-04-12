class Student(object):
	def __init__(self, name, score):
		self.__name = name          #__xxx represent private viarible
		self.__score = score

	def get_name(self):
		return self.__name
	def get_score(self):
		return self.__score

	def print_score(self):
		print '%s: %s' %(self.__name, self.__score)

bart = Student('bart Simpson', 98)
lisa = Student('lisa Simpson', 77)
print bart.get_name()
print lisa.get_name()
print bart.get_score()
print lisa.get_score()
bart.print_score()
lisa.print_score()
