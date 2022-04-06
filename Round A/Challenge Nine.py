m = int(input())
for i in range(1, m+1):
	n = int(input())
	d = (-n) % 9
	s = [int(_) for _ in str(n)]
	flag = False
	for j in range(len(s)):
		if d < s[j]:
			if d == 0 and j == 0:
				continue
			else:
				s = s[:j] + [d] + s[j:]
				flag = True
				break
	# if not flag:
		# for j in range(len(s)):
		# 	if d == s[j]:
		# 		s = s[:j] + [d] + s[j:]
		# 		flag = True
		# 		break
	if not flag:
		s = s + [d]
	print(f'Case #{i}: ' + ''.join(map(str, s)))