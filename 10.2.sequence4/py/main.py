import random
s = []
n = 1000
for i in range(0, n):
  s.append(str(random.randint(1, 105)))
print(' '.join(s))
f = open('input.txt', 'w')
f.write(str(n) + '\n')
f.write(' '.join(s))
f.close()