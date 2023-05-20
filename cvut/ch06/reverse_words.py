

def reverse_words(s):

    # pass 1: reverse string
    s = list(s)
    for i in range(len(s) // 2):
        temp = s[i]
        s[i] = s[len(s)-i-1]
        s[len(s) - i - 1] = temp

    # pass 2: swap words
    j = 0
    in_word = False
    print(s)

    to_remove = []

    for i in range(0, len(s)):

        # look for start of word
        if s[i].isalnum() and not in_word:
            in_word = True
            j = i

        # look for end of word
        if not s[i].isalnum() and in_word:
            in_word = False
            print(s[j], s[i])

            # flip word
            k = 0
            word_len = i - j + 1
            while k < (word_len // 2):
                print(s[j + k], s[i - k -1])
                temp = s[j + k]
                s[j + k] = s[i - k - 1]
                s[i - k - 1] = temp
                k += 1
            print('here')

        i += 1
    
    if in_word:
        
        # flip word
        k = 0
        word_len = i - j + 1
        while k < (word_len // 2):
            print(s[j + k], s[i - k -1])
            temp = s[j + k]
            s[j + k] = s[i - k - 1]
            s[i - k - 1] = temp
            k += 1
        print('here')

    in_word = False

    # prune whitespace
    result = []
    cur_word = ''
    for i in range(len(s)):

        if not in_word and not s[i].isalnum():
            pass

        elif not in_word and s[i].isalnum():
            cur_word = s[i]
            in_word = True
                    
        elif in_word and not s[i].isalnum():
            result.append(cur_word)
            in_word = False
            cur_word = ''
        
        else:
            cur_word += s[i]
        
        i+=1

    if cur_word:
        result.append(cur_word)

    return ' '.join(result)

def reverse_words_2(s):
    temp = s.split()
    temp.reverse()
    return ' '.join(temp)

print(reverse_words_2("bob likes alice"))
print(reverse_words_2("isaac was hunting in jersey"))
print(reverse_words_2(" hello world "))