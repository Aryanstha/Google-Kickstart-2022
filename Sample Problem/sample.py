import sys

# Read input from stdin
input = sys.stdin.readlines()
cases = int(input.pop(0))

tests = {}
for i in range(cases):
    N, M = input.pop(0).split(" ")
    C = [int(x) for x in input.pop(0).split(" ")]
    tests[i+1] = {"N": int(N), "M": int(M), "C": C}
 
# Remainder function
def remainder(N, M, C):
    return sum(C) % M

# Output
for t in tests:
    test = tests[t]
    s = remainder(test["N"], test["M"], test["C"])
    print(f"Case #{t}: {s}")
