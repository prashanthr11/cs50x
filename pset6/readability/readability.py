from cs50 import get_string

s = get_string('Text:')  # Getting Input

letters = words = 1.0
index = 0
sentences = 0.0

for i in range(1, len(s)):  # Loop through the string
    if s[i] == " ":  # Word Count
        words += 1
        if s[i + 1] == ' ':  # Adjacent Spaces Count
            words -= 1
    elif s[i] == ',' or s[i] == "'":    
        i += 1
    elif s[i].isalpha() or s[i] == '-':  # Alphabets & Hyphen Count
        letters += 1
        
sentences = s.count('.') + s.count('!') + s.count('?')  # Sentences Count
L_Per_W = (letters / words) * 100  # Counting Averages
S_Per_W = (sentences / words) * 100  # Counting Averages
X = 0.0588 * L_Per_W - 0.296 * S_Per_W - 15.8
index = round(X)
if index < 0:
    print('Before Grade 1')
elif index > 16:
    print('Grade 16+')
else:
    print("Grade {}".format(index))