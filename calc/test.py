from enum import Enum

class TokenType(Enum):
  NUMBER_LITERAL    = 1
  OP_MULT           = 2
  OP_SUB            = 3
  OP_ADD            = 4
  OP_DIV            = 5
  OPEN_PARENTH      = 6
  CLOSE_PARENTH     = 7

class Token:
  
  def __init__(self, tok):
    self.tok: str = tok
    self.val = 0.0
    self.token_type: TokenType = None

  def parse_token(self):

    if(self.tok.isnumeric()):
      self.convert_to_float(self.tok)
      self.token_type = TokenType.NUMBER_LITERAL
    elif self.tok in '-+/*':
      self.is_operator(self.tok)
    elif self.tok == ')':
      self.token_type = TokenType.CLOSE_PARENTH
    elif self.tok == '(':
      self.token_type = TokenType.OPEN_PARENTH
    else:
      print("%s is not a valid token"%(self.tok))
      exit(1)


  def convert_to_float(self, val):
    try:
      self.val = float(val)
    except ValueError:
      print("%s is not able to be converted to a floating point number"%(val))
      exit(1)

  def is_operator(self, val):
    if val == '*':
      self.token_type = TokenType.OP_MULT
    elif val == '+':
      self.token_type = TokenType.OP_ADD
    elif val == '-':
      self.token_type = TokenType.OP_SUB
    elif val == '/':
      self.token_type = TokenType.OP_DIV

# globals

token_list: Token = []


def parse_token(val):
  tok = Token(val)
  tok.parse_token()
  token_list.append(tok)

def lex(expr):
  counter: int = 0
  is_parsing_number: bool = False
  parse_num: str  = ''
  len_expr: int = len(expr)
  while True:
    if(counter > len_expr-1):
      break
      # print(counter)
    char = expr[counter]


    if(char.isnumeric()):
      is_parsing_number = True
      parse_num += char
      if(counter == len_expr-1):
        parse_token(parse_num)          
        break
        
      # print("h")
    else:
      if(is_parsing_number == True):
        parse_token(parse_num)          
          
        is_parsing_number = False
        parse_num = ''
        continue
      else:
        parse_token(char)          


    counter += 1
        


def solve_two(x: int, y: int, op: TokenType) -> int: 
  if(op == '-'):
    return x - y
  elif(op == '+'):
    return x + y
  elif(op == '/'):
    return x / y;
  elif(op == '*'):
    return x * y

def get_token(loc: int, length: int):
  if(loc >= length):
    return None
  return token_list[loc]



def parse() -> int:
  # parse_groups: TokenType = []
  result: float = 0.0

  # counter
  i: int = 0
  num_tokens: int = len(token_list)
  while True:
    if(i > num_tokens-1):
      break;

    if(get_token(i,num_tokens).token_type == TokenType.OP_MULT):
      x = get_token(i-1, num_tokens)
      y = get_token(i+1, num_tokens)
      if(x == None or y == None):
        print("Syntax error")
      res = solve_two(x, y, TokenType.OP_MULT)

      token_list[i].val = res
      token_list[i].token_type = TokenType.NUMBER_LITERAL
      token_list.remove(get_token(i-1, num_tokens))
      token_list.remove(get_token(i+1, num_tokens))



    i += 1


  return result



def dump_token_list():
  for i in token_list:
    if(i.token_type == TokenType.NUMBER_LITERAL):
      print("{}: {}".format(i.token_type, i.val))
    else:
      print(i.token_type)




def main():

  expr = ''

  while True:
    try:
      expr = input(">")
    except KeyboardInterrupt:
      exit(0)


    if(expr == 'exit'): 
      break

    expr = ''.join(expr.split(' '))
    lex(expr)
    
    print(parse())
    dump_token_list()
    token_list.clear()


if __name__ == '__main__':
  main()