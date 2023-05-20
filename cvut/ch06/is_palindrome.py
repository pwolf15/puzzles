
def is_palindrome(s):

    valid = True
    i = 0
    j = len(s) - 1
    
    while i < j:
        if not s[i].isalnum():
            i += 1
            continue
        if not s[j].isalnum():
            j -= 1
            continue
        if s[i].lower() != s[j].lower():
            valid = False
            break
        i += 1
        j -= 1
    return valid
    
print(is_palindrome('abba'))
print(is_palindrome(''))
print(is_palindrome('racecar'))
print(is_palindrome('tact'))
print(is_palindrome(''))
print(is_palindrome('A man, a plan, a canal, Panama.'))
print(is_palindrome('Able was I, ere I saw Elba!'))
print(is_palindrome('Ray a ray'))