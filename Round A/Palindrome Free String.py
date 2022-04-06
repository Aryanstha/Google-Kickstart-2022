def check(s, t):
	for i in range(len(s)):
		if s[i] == '?' or s[i] == t[i]:
			continue
		else:
			return False
	return True

valid = ['001011', '001101', '010011', '010110', '011001', '011010', '100101', '100110', '101001', '101100', '110010', '110100']

N = 14

from itertools import product

shorts = [set() for _ in range(N+1)]

for n in range(1, N+1):
	for p in product(('0', '1'), repeat=n):
		s = ''.join(p)
		flag = False
		for i in range(n-4):
			if p[i] == p[i+4] and p[i+1] == p[i+3]:
				flag = True
				break
		for i in range(n-5):
			if p[i] == p[i+5] and p[i+1] == p[i+4] and p[i+2] == p[i+3]:
				flag = True
				break
		if not flag:
			shorts[n].add(s)

def correct(s):
	n = len(s)
	ans = False
	if n <= N:
		for t in shorts[n]:
			if check(s, t):
				return True
	else:
		flag = False
		nn = n-6
		for v in valid:
			temp = s
			seed = v * (nn//6) + v[:(nn%6)]
			if check(temp[3:-3], seed):
				temp = temp[:3] + seed + temp[-3:]
				for one in shorts[6]:
					if check(temp[:6], one):
						for two in shorts[6]:
							if check(temp[-6:], two):
								flag = True
								temp = one + temp[6:-6] + two
								break
					if flag:
						break
			if flag:
				break
		return flag
	return ans

m = int(input())
for case in range(1, m+1):
	n = int(input())
	s = input()
	ans = correct(s)
	print(f'Case #{case}: ' + ('POSSIBLE' if ans else 'IMPOSSIBLE'))

# count = 0
# for p in product(('0', '1'), repeat=12):
# 	s = ''.join(p)
# 	if correct(s):
# 		print(s)
# 		count += 1
# print(count)
