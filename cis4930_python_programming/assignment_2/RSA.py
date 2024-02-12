# Marlan McInnes-Taylor mm05f
import math, random
class RSA(object):
    def __init__(self):
        self.e = 0
        self.d = 0
        self.N = 0
        self.messageList = []
    
    def LCM(self, num1, num2):
        lcm = (num1*num2)//self.GCD(num1,num2)
        return lcm

    def GCD(self, num1, num2):
        while(num2):
            num1, num2 = num2, num1 % num2 
        return num1

    def Totient(self, p, q):
        return int((p-1)*(q-1))

    def calcD(self, e, phi):
        for x in range(1, phi):
            if (e * x) % phi == 1:
                return x
        return None


    def inputFunc(self):
        numEntries = int(input('Enter the number of messages: '))

        print('Enter the messages:')
        for i in range (0,numEntries):
            self.messageList.append(int(input()))

    def printFunc(self, message):
        return 'message is ' + str(message)

    def primeGen(self, minimum):
        findPrime = minimum
        isPrime = True

        while True:
            findPrime += 1
            for i in range(2, int(math.sqrt(findPrime))+1):
                if findPrime % i == 0:
                    isPrime = False
                    break                    
            if isPrime == False:
                isPrime = True
            else:
                yield int(findPrime)
                
        
    def keyGen(self):
        minimum = int(input('Enter the minimum value for the prime numbers: '))
        primes = self.primeGen(minimum)

        p = next(primes)
        q = next(primes)

        self.N = p * q
        phi = self.Totient(p, q)

        while True:
            e = random.randrange(2, phi)
            if self.GCD(e, phi) == 1:
                self.e = e
                break

        self.d = self.calcD(self.e, phi)
                
        print('N is ', self.N)
        print('e is ', self.e)
        
    def encrypt(self, message):
        return pow(int(message), self.e, self.N)

    def decrypt(self, message):
        return pow(int(message), self.d, self.N)

    def encDecorate(self, func):
        def func_wrapper(message):
            return 'The encrypted ' + func(message)
        return func_wrapper
    
    def decDecorate(self, func):
        def func_wrapper(message):
            return 'The decrypted ' + func(message)
        return func_wrapper
        
    def messages(self):
        self.inputFunc()
        self.keyGen()

        encMessages = []

        msgItr = iter(self.messageList)

        while True:
            try:
                message = next(msgItr)
                encMessages.append(self.encrypt(message))
            except StopIteration:
                break

        eDec = self.encDecorate(self.printFunc)
        for encMsg in encMessages:
            print(eDec(encMsg))

        dDec = self.decDecorate(self.printFunc)
        for encMsg in encMessages:
            print(dDec(self.decrypt(encMsg)))
        

if __name__ == "__main__":
    rsaObj = RSA()
    rsaObj.messages()
