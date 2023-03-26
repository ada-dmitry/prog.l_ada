'''
print("Введите размер массива: ")
n = int(input())
a = [int(input()) for i in range(n)]
'''
a = [4,3,2,5,1]
b = a.copy()
def sortSelect(arr):
    for i in range(len(arr)-1):
        ind = i
        for j in range(i+1, len(arr)):
            if(arr[ind]>arr[j]): 
                ind = j
        arr[i], arr[ind] = arr[ind], arr[i]
    return arr


def sortInsert(arr):
    for i in range(len(arr)):
        j = i-1
        x = arr[i]
        while((arr[j]>x)and(j>=0)):
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = x
    return arr
        

    
print(sortSelect(a), sortInsert(b))