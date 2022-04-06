def ok(n):
	one = 1
	two = 0
	while n > 0:
		i = n % 10
		one *= i
		two += i
		n //= 10
	return (one % two == 0)

import heapq
# from math import ceil
# key gen
pq = [(1, 0)]
NMAX = 12 # 13
SMAX = 9*(NMAX) + 9 # 120
PMAX = 9**(NMAX) * 9 # 9**12
keys = []
recent = 0
while pq:
	i, d = heapq.heappop(pq)
	cand = [(_*i, d+1) for _ in range(2, 9+1)]
	flag = True
	if recent != i:
		keys.append(i)
		if d < NMAX:
			for j in cand:
				if j[0] <= PMAX:
					heapq.heappush(pq, j)
		recent = i

keys = [0] + keys
keyset = set(keys)

dp = [[{p: 0 for p in keys} for _ in range(SMAX)] for _ in range(NMAX)]
for s in range(1, SMAX):
	for p in keys:
		dp[0][s][p] = (1 if (p%s == 0) else 0)
for n in range(1, NMAX + 1):
	for s in range(1, 9 * (NMAX - n) + 1):
		for p in keys:
			if p > 9 ** (NMAX - n):
				break
			for i in range(9+1):
				if s+i >= SMAX:
					break
				if p*i not in keyset:
					continue
				dp[n][s][p] += dp[n-1][s+i][p*i]

for case in range(1, int(input()) + 1):
	a, b = map(int, input().split())
	ans = 0
	while a <= b:
		mult = 10**14
		while (a % mult != 0) or a+mult > b+1:
			mult //= 10
		x, y = a, a+mult-1
		# print(f'{x=} {y=}')
		n = len(str(x))
		m = n
		s = 0
		p = 1
		for i in range(m):
			if str(x)[i] == str(y)[i]:
				s += int(str(x)[i])
				p *= int(str(x)[i])
				n -= 1
		# print(f'{n=} {s=} {p=} {dp[n][s][p]=}')
		ans += dp[n][s][p]
		a = a+mult
	print(f'Case #{case}: {ans}')