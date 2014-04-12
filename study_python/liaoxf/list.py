#!/usr/bin/env python
# -*- coding: utf-8 -*-
classmates = ['Micheal', 'Bob', 'Tracy']
print classmates
print len(classmates)
print 'First:  %s.\n'   %(classmates[0]),
print 'Second: %s.\n'   %(classmates[1]),
print 'Third:  %s.\n\n' %(classmates[2]),
#'Forth:  %s' %(classmates[3]),'\n\n',
print 'Reversed First:  %s.\n'   %(classmates[-1]),
print 'Reversed Second: %s.\n'   %(classmates[-2]),
print 'Reversed Third:  %s.\n\n' %(classmates[-3]),
#'Reversed Forth:  ', classmates[-4],'\n','\n',
name = 'Jack'
classmates.insert(1, name),
print 'Then, we add %s after %s.\n' % (name,'Michael'),
print 'So, First:  %s.\n'   %(classmates[0]),
print 'So, Second: %s.\n'   %(classmates[1]),
print 'So, Third:  %s.\n'   %(classmates[2]),
print 'So, Forth:  %s.\n\n' %(classmates[3]),

name = 'Adam'
classmates.append(name),
print 'Besides, we add %s at last.\n' % (name),
print 'Finally, First: %s.\n'   %(classmates[0]),
print 'Finally, Second:%s.\n'   %(classmates[1]),
print 'Finally, Third: %s.\n'   %(classmates[2]),
print 'Finally, Forth: %s.\n'   %(classmates[3]),
print 'Finally, Fifth: %s.\n\n' %(classmates[4]),
print 'Then, We delete last ss--%s.\n'%(classmates[-1]),
classmates.pop(-1),

print 'Finally, First: %s.\n'   %(classmates[0]),
print 'Finally, Second:%s.\n'   %(classmates[1]),
print 'Finally, Third: %s.\n'   %(classmates[2]),
print 'Finally, Forth: %s.\n\n' %(classmates[3]),
classmates[0] = ['Michael','60'],
print 'Congratulations! %s\'s score is %d.\n'%(classmates[0][0],classmates[0][1]),
