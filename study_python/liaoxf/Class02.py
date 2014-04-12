class Student(object):
	def __init__(self, name, score):
		self.name = name
		self.score = score

	def print_score(self):
		print '%s: %s' %(self.name, self.score)

bart = Student('bart Simpson', 98)
lisa = Student('lisa Simpson', 77)
bart.print_score()
lisa.print_score()
