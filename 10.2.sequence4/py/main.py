import random
s = []
n = 1000
m = 10 ** 9
for i in range(0, n):
  s.append(str(random.randint(1, m)))
print(' '.join(s))
f = open('input.txt', 'w')
f.write(str(n) + '\n')
f.write(' '.join(s))
f.close()