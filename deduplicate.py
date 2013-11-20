
def remove_at(li, n):
    size = len(li)
    if n > size - 1:
        return
    i = n
    while i < size - 1:
        li[i] = li[i + 1]
        i = i + 1
    del li[i]

def find(li, lo, hi, n):
    i = lo
    while i < hi and li[i]!=n:
        i = i + 1
    if i==hi:
        return -1
    return i

def deduplicate(li):
    if li==None:
        return
    i = 1
    while i < len(li):
        pos = find(li, 0, i, li[i])
        if pos == -1:
            i = i + 1
        else:
            remove_at(li, i)
        


