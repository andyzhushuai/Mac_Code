def func(a, b, c=0, *args, **kw):
	print 'a =', a, 'b =', b, 'c =', c, 'args =', args, 'kw =', kw

func(1, 2)
func(1, 2, x=99)
func(1, 2, 3)
func(1, 2, 3, 'a', 'b')
func(1, 2, 3, 'a', x=99)
func(1, 2, 3, x=99)
func(1, 2, 3, 'a', 'b', x=99)

args01 = (1, 2, 3, 4)
args02 = (1, 2, 3, 'a')
args03 = (1, 2, 3, 'a', 'b')
kw = {'x': 99}
func(*args01, **kw)
func(*args02, **kw)
func(*args03, **kw)
