# dic could change length!!!
d = {'Michael': 95, 'Bob': 75, 'Tracy': 85}
print d['Michael'],
print d.get('Michael')
d.get('Michael',100),
print d.get('Michael')
d['Michael'] = 100
print d.get('Michael')
d.pop('Michael'),
print d
#name = 'Adam',
#d.append(name),
#d[name] = 67,
#print d.['Adam']
#print d['Adam']
#d.get('Thomas')
#d.get('Thomas', -1)
#print 'Thomas' in d
