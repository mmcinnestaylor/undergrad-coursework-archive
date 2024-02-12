# Marlan McInnes-Taylor mm05f
def isPalindrome(word):
    strippedWord = word.replace(" ", "")
    strippedWord = strippedWord.lower()
    if strippedWord == strippedWord[::-1]:
        return True
    return False

if __name__ == "__main__":
    usrInput = []
    palindromes = {}

    word = input("Enter the strings:\n")

    while word != "Done":
        usrInput.append(word)
        word = input()

    for i,word in enumerate(usrInput):
        if isPalindrome(word):
            palindromes[i+1] = word
    
    print("The palindromes are:\n", palindromes)
