def search_min_k(lst_A: list, val: int) -> int:
    index = 1
    while index < len(lst_A) and lst_A[index] < val :
        index *= 2
    if index > len(lst_A):
        index = len(lst_A)
    if val > lst_A[len(lst_A) - 1]:
        return len(lst_A)
    left = 0
    right = index
    while right - left > 1:
        mid = (right + left) // 2
        if lst_A[mid] >= val:
            right = mid
        else:
            left = mid
    if lst_A[left] >= val:
        return left
    return right


n, m = map(int, input().split())
lst_A = [int(x) for x in input().split()]
lst_B = [int(y) for y in input().split()]
for i in range(len(lst_B)):
    print(search_min_k(lst_A, lst_B[i]))