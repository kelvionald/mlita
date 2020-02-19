def pushing(stack, result):
  l = len(stack)
  for i in range(0, l):
    s = stack.pop()
    if s == '(':
      break
    result.append(s)

def postfix(tokens):
  result = []
  stack = []
  priority = {
    '-': 1,
    '+': 1,
    '*': 2,
    '/': 2
  }
  ops = priority.keys()
  for t in tokens:
    if t.isdigit():
      result.append(t)
    elif len(stack) == 0 or stack[-1] == '(':
      stack.append(t)
    elif t in ops and stack[-1] in ops and priority[t] > priority[stack[-1]]:
      stack.append(t)
    elif t in ops:
      pushing(stack, result)
      stack.append(t)
    elif t == '^':
      stack.append(t)
    elif t == '(':
      stack.append(t)
    elif t == ')':
      pushing(stack, result)
  pushing(stack, result)
  return result

def getAB(stack, f):
  a = float(stack.pop())
  b = float(stack.pop())
  print(a, b, f(b, a))
  return f(b, a)

def calc(tokens):
  stack = []
  for t in tokens:
    if not t.isdigit():
      print(t)
    if t.isdigit():
      stack.append(t)
    elif t == '-':
      stack.append(getAB(stack, lambda a, b: a - b))
    elif t == '+':
      stack.append(getAB(stack, lambda a, b: a + b))
    elif t == '*':
      stack.append(getAB(stack, lambda a, b: a * b))
    elif t == '/':
      stack.append(getAB(stack, lambda a, b: a / b))
    elif t == '^':
      stack.append(getAB(stack, lambda a, b: a ** b))
  return stack[0]

# http://primat.org/news/obratnaja_polskaja_zapis/2016-04-09-1181

def answer(expr, antipolsk):
  print(postfix(list(expr)) == list(antipolsk), calc(postfix(list(expr))), eval(expr.replace('^', '**')))

answer('1-2+7', '12-7+')
answer('1+2-4*2', '12+42*-')
answer('(1+2)*2', '12+2*')
answer('(1*2)-1', '12*1-')
answer('(1+2*7)/4', '127*+4/')
answer('(1*(2+2)+3)/2', '122+*3+2/')
answer('1^2^3', '123^^')
answer('1^(2*8^9)', '1289^*^')
answer('1*(2+4)^(9-3)', '124+93-^*')
answer('1*2*3*4+1+2*4', '12*3*4*1+24*+')
answer('(1+2)^2-7', '12+2^7-')