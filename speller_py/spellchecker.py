import string
from sys import argv

def main():
    if len(argv) != 2:
        print("Usage: ./spellchecker.py textfile")
        exit()
    load("large")
    text = open(argv[1])
    for line in text:      
         for word in line.split():
              check(word)
    text.close
    

palavras = set()


def load(dict):
    arguivo = open(dict, "r")
    for line in arguivo:
        palabrajaja = line.rstrip()
        palavras.add(palabrajaja)
    arguivo.close


def check(palavra):
    cleaned = palavra.translate(str.maketrans("", "", string.punctuation))
    if cleaned.lower() in palavras:
        return True
    print(cleaned)
    return False


def size():
    return len(palavras)


main()