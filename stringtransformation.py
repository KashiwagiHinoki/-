#String Transformation
import string

def solve():
    s = input()
    t = input()

    dict_s = dict()
    dict_t = dict()
    for c in string.ascii_lowercase:
        dict_s[c] = []
        dict_t[c] = []

    for i, _s in enumerate(s):
        dict_s[_s].append(i)
    for i, _t in enumerate(t):
        dict_t[_t].append(i)
    
    is_ans = True
    for _dict_s in dict_s.values():
        if _dict_s not in dict_t.values():
            is_ans = False
            break

    if is_ans:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    solve()
