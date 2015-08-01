
fout = open("primec.out", "wt")

def next_int(fname):
    for line in open(fname):
        for val in line.split():
            yield int(val)

def isPrime(x):
	if ( (x < 2) or (x % 2 == 0 and x > 2) ) :
		return False

	i = 3

	while(i * i < x + 1):
		if x % i == 0:
			return False

	return True


for n in next_int("primec.in"):
	fout.write("%s" % "YES\n" if (isPrime(n) == 1) else "NO\n")
