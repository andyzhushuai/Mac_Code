def calc(*numbers):
	sum = 0
	for n in numbers:
		sum = sum + n * n
	return sum

l01 = [1, 2, 3]
t01 = (1, 3, 5, 7)
print calc(*l01)
print calc(*t01)
