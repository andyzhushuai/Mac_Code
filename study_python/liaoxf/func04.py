def my_abs(x):
#		if not isinstance(x, (int, double)):
		if not isinstance(x, (int, float)): # in Python, float == double in C/C++.
				raise TypeError('bad operand type')
		if x >= 0:
			return x
		else:
			return -x
print my_abs('A')
print my_abs(123)
print my_abs(-123)
