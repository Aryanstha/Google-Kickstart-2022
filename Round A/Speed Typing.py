n = int(input())
for i in range(1, n+1):
	s = input()
	t = input()
	a = 0
	b = 0
	while a < len(s) and b < len(t):
		if s[a] == t[b]:
			a += 1
			b += 1
		else:
			b += 1
	if a < len(s):
		print(f"Case #{i}: IMPOSSIBLE")
	else:
		print(f"Case #{i}: " + str(len(t) - len(s)))