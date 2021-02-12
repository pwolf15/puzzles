
def countSegments(s):
    return len(s.split())

def addStrings(num1, num2):
    """
    :type num1: str
    :type num2: str
    :rtype: str
    """

    less = num1 if len(num1) < len(num2) else num2
    greater = num1 if len(num2) >= len(num1) else num2

    return ""

def numberOfSteps (num):
    """
    :type num: int
    :rtype: int
    """

    steps = 0
    while num:
        steps += 1
        if num % 2 == 0:
            num /= 2
        else:
            num -= 1

    return steps


print(countSegments("welcome to the jungle"))
print(countSegments("Hello, my name is John"))
print(addStrings("12", "23"))
print(numberOfSteps(1))
print(numberOfSteps(14))
print(numberOfSteps(7))
print(numberOfSteps(6))