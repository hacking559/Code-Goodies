
'''
Consider that you are reading a number n from the file sieve.in
This script factorises all of the numbers less or equal to n into prime factors.
Enjoy! :D 

Copyright Tudor Coman 2015. All rights reserved.

'''
sieve = [1, 1]

fout = open("sieve.out", "wt")

def next_int(fname):
    for line in open(fname):
        for val in line.split():
            yield int(val)

def simple_sieve(nr):
	i = 4
	while (i < nr + 1):
		sieve[i] = 1
		i += 2
	i = 3
	while(i * i < nr + 1):
		if sieve[i] == 0:
			j = i * i
			while(j < nr + 1):
				sieve[j] = 1
				j += 2 * i
		i += 2



def special_sieve(nr):
	i = 4
	while (i < nr + 1):
		sieve[i] = 2
		i += 2
	i = 3
	while(i * i < nr + 1):
		if sieve[i] == 0:
			j = i * i
			while(j < nr + 1):
				sieve[j] = i
				j += 2 * i
		i += 2

def prime_factorisation(nr):

	if nr == 1:
		fout.write("\n")
		return

	if sieve[nr] == 0:
		fout.write("%d^1\n" % (nr)) 
		return

	div = sieve[nr]
	exp = 0
	no = nr
	while (nr % div == 0):
		nr /= div
		exp += 1

	fout.write("%d^%d " % (div, exp)) 
	prime_factorisation(nr)

for n in next_int("sieve.in"):
	''' Initialize the sieve vector'''
	for i in range(2, n + 1):
		sieve.append(0)

	special_sieve(n)
	for i in range(2, n + 1):
		fout.write("%d: " % (i)) 
		prime_factorisation(i)

fout.close()

