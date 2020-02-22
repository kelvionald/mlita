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
  deb = False
  ops = priority.keys()
  for t in tokens:
    if (deb): print(t, result, stack)
    if t.isdigit():
      result.append(t)
    elif len(stack) == 0 or stack[-1] == '(':
      stack.append(t)
    elif t in ops and stack[-1] in ops and priority[t] > priority[stack[-1]]:
      stack.append(t)
    elif t in ops and stack[-1] in ops and priority[t] == priority[stack[-1]]:
      s = stack.pop()
      result.append(s)
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
    if (deb): print(t, result, stack)
    if (deb): print('-'  *10)
  pushing(stack, result)
  return result

def getAB(stack, f):
  a = float(stack.pop())
  b = float(stack.pop())
  return f(b, a)

def calc(tokens):
  stack = []
  for t in tokens:
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
  antipols = postfix(list(expr))
  cm = antipols == list(antipolsk)
  print(cm, calc(postfix(list(expr))), eval(expr.replace('^', '**')))
  if not cm:
    print(' 1 ' + antipolsk)
    print(' 0 ' + ''.join(antipols))

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
answer('1/1-1/2+1/(2*3)-1/(2*3*4)+1/(2*3*4*5)-1/(2*3*4*5*6)+1/(2*3*4*5*6*7)-1/(2*3*4*5*6*7*8)+1/(2*3*4*5*6*7*8*9)', '11/12/-123*/+123*4*/-123*4*5*/+123*4*5*6*/-123*4*5*6*7*/+123*4*5*6*7*8*/-123*4*5*6*7*8*9*/+')
answer('1/(2*3*4)+1/(2*3*4*5)-1/(2*3*4*5*6)+1/(2*3*4*5*6*7)-1/(2*3*4*5*6*7*8)+1/(2*3*4*5*6*7*8*9)', '123*4*/123*4*5*/+123*4*5*6*/-123*4*5*6*7*/+123*4*5*6*7*8*/-123*4*5*6*7*8*9*/+')
answer('1/(2*3*4)+1/(2*3*4*5)', '123*4*/123*4*5*/+')
answer('1/(2*3*4*5)', '123*4*5*/')
answer('(1+2+3)/(2*3*4*5)', '12+3+23*4*5*/')
