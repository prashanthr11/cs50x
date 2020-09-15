from string import ascii_lowercase as lc
from collections import deque

table = list()
    

def fill_table():
    for i in range(26):
        table.append(lc)
        
    for i in range(len(lc)):
        table[i] = lc[i:] + lc[:i]

def vignere_cipher_encrypt(a, b):
    return table[ord(a) - 97][ord(b) - 97]

def vignere_cipher_decrypt(a, b):
    return table[0][table[ord(a) - 97].index(b)]
    
p = input().replace(' ', '').lower()
key = input().replace(' ', '').lower()



i = 0
while len(key) < len(p):
    key += key[i % len(key)]
    i += 1

while len(key) > len(p):
    p += p[i % len(p)]
    i += 1
    
fill_table()

cipher_text = ''

for i in range(max(len(p), len(key))):
    cipher_text += vignere_cipher_encrypt(p[i], key[i])
    
print("The Cipher Text is :", cipher_text)

Decrypted_text = ''

for i in range(len(p)):
    Decrypted_text += vignere_cipher_decrypt(key[i], cipher_text[i])
    
print("The Decrypted Text is :", Decrypted_text)