
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

# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def gen_list(l1):
    dummy = ListNode(0)
    head = dummy.next
    head = ListNode(l1[0])
    print("len: " + str(len(l1)))
    for el in l1:
        print("HERE!")
        head.next = ListNode(el)
        # head = head.next
    print(head)
    return head


print(countSegments("welcome to the jungle"))
print(countSegments("Hello, my name is John"))
print(addStrings("12", "23"))
print(numberOfSteps(1))
print(numberOfSteps(14))
print(numberOfSteps(7))
print(numberOfSteps(6))

        
l1 = ListNode(1)
l2 = ListNode(2)
print(l1.val)
print(l2.val)
l1.next = l2
while l1:
    print(l1.val)
    l1 = l1.next
l1 = gen_list([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
while l1:
    print(l1.val)
    l1 = l1.next