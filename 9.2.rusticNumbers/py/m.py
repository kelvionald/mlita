N = 10000000

s = N - (N//2 + N//3 + N//5 - N//6 - N//10 - N//15 + N//30)

print(s)
print()

сумма = 0
for i in range(1, N + 1, 2):
    if i % 3 != 0 and i % 5 != 0:
        сумма += 1
    if i % 10000 == 0:
        print(i)

print(сумма)
