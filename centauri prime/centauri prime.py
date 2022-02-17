def get_ruler(kingdom):
    
    vowels = ['A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u']
    y = ['Y', 'y']

    if kingdom[-1] in vowels:
        return "Alice"
    elif kingdom[-1] in y:
        return "nobody"
    else:
        return "Bob"


def main():
    # Get the number of test cases
    T = int(input())
    for t in range(T):
        # Get the kingdom
        kingdom = input()
        print('Case #%d: %s is ruled by %s.' % (t + 1, kingdom, get_ruler(kingdom)))

if __name__ == '__main__':
  main()
