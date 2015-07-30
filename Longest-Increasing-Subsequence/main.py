
from collections import deque

fo = open("lis.out", "wt")

def lowerBound(vec, lo, hi, target):
	if lo > hi:
		return lo
	mid = (lo + hi) / 2

	if vec[mid] >= target:
		return lowerBound(vec, lo, mid - 1, target)
	else:
		return lowerBound(vec, mid + 1, hi, target)
		
### The 2 LIS Algorithms: O(N ^ 2) and O(N log N) ###

def N_sq(n, v):
	L = []
	next = []

	steps = n

	while(steps):
		L.append(0)
		next.append(0)
		steps -= 1

	L[n - 1] = 1

	for i in range(n - 2, -1, -1):
		L[i] = 1
		next[i] = 0

		for j in range(i + 1, n):
			if v[i] < v[j] and L[j] + 1 > L[i]:
				L[i] = L[j] + 1
				next[i] = j

	lis = L[0]
	pos = 0

	for i in range(1, n):
		if L[i] > lis:
			lis = L[i]
			pos = i

	fo.write("%d\n" % (lis))


	while(pos):
		fo.write("%d " % (v[pos]))
		pos = next[pos]

def N_log_N(n, v):
	p = []
	q = []
	steps = n

	while(steps):
		p.append(0)
		q.append(0)
		steps -= 1

	q[0] = v[0]
	p[0] = 1
	sq = 1

	for i in range(0, n):
		pos = lowerBound(q, 0, sq - 1, v[i])
		if pos == sq:
			q[sq] = v[i]
			p[i] = sq
			sq += 1
		else:
			q[pos] = v[i]
			p[i] = pos

	fo.write("%d\n" % (sq))

	target = sq - 1
	sol = deque()

	for i in range(n - 1, -1, -1):
		if p[i] == target:
			sol.appendleft(v[i])
			target -= 1

	for elem in sol:
		fo.write("%d " % (elem))


with open('lis.in') as f:
	line = f.readline()
	for x in line:
		n = int(x)
		break
	line = f.readline()
	v = [int(x) for x in line.split()]
	N_log_N(n, v)
