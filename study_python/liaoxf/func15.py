def add_end01(L=[]):
	L.append('END')
	return L

def add_end02(L=None):
	if L is None:
		L = []
		L.append('END')
	return L

l01 = ['x', 'y', 'z']

#print add_end01(l01)
#print add_end01(l01)
#print add_end01(l01)

print add_end02(l01)
print add_end02(l01)
print add_end02(l01)
print add_end02()
