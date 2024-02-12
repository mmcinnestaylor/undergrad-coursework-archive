# Marlan McInnes-Taylor mm05f
def printTriangle(rows):
    temp = []
    pascal = []

    for row in range(0,rows):
        for x in range(0,row+1):
            if x == 0 or x == row:
                temp.append(1)
            else:
                temp.append(pascal[row-1][x-1] + pascal[row-1][x])
        pascal.append(temp)
        temp = []
  
    for row in range (0,rows):
        for x in pascal[row]:
            print(x, end = ' ')
        print()

if __name__ == "__main__":
    N = int(input("Enter the number of rows: "))
    printTriangle(N)
