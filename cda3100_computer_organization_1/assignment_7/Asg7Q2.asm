.data
quitCond: .float 999.0
exitCond: .float 0.0000000000000001
inputPrompt: .asciiz "Let's test our exponential function!\nEnter a value for x (or 999 to exit): "
returnPrompt: .asciiz "Our approximation for e^"
returnPrompt2: .asciiz " is "
goodbye: .asciiz "Come back soon!"
newline: .asciiz "\n"

  .text
  .globl main
main:
  l.s $f11, quitCond

loop:
  la $a0, inputPrompt
  li $v0, 4
  syscall

  li $v0, 6
  syscall

  c.eq.s $f11, $f0
  bc1t exit

  mov.s $f12, $f0
  jal exp

  la $a0, returnPrompt
  li $v0, 4
  syscall

  li $v0, 2
  syscall

  la $a0, returnPrompt2
  li $v0, 4
  syscall

  mov.s $f12, $f0
  li $v0, 2
  syscall

  la $a0, newline
  li $v0, 4
  syscall

  j loop

exit:
  la $a0, goodbye
  li $v0, 4
  syscall

	li $v0, 10
	syscall

exp:
  li $t0, 0
  li $t1, 1

  mtc1 $t1, $f0
  cvt.s.w $f0, $f0             #initialize return register

  mtc1 $t0, $f29
  cvt.s.w $f29, $f29           #used in comparisons against value of 0

  mtc1 $t1, $f30
  cvt.s.w $f30, $f30           #for incrementing by 1

  c.eq.s $f12, $f29            #compare parameter against 0
  bc1t expEnd                  #if parameter is 0, exit

  l.s $f2, exitCond            #stores exit condition

  mtc1 $t1, $f3
  cvt.s.w $f3, $f3             #loop test registers

  mtc1 $t1, $f4
  cvt.s.w $f4, $f4             #x/(i+1) register

  mtc1 $t1, $f6
  cvt.s.w $f6, $f6             #incrementing register for factorial

  mtc1 $t1, $f7
  cvt.s.w $f7, $f7             #stores new term to add to sum

  abs.s $f8, $f12              #use absolute value of parameter in summation

summation:
   div.s $f4, $f8, $f6         #creating x/(i+1)

   add.s $f6, $f6, $f30        #increment factorial register

   mul.s $f7, $f7, $f4         #create new term for summation
   div.s $f3, $f7, $f0         #divide new term by summation

   c.le.s $f3, $f2             #if new term/sum < 1.0*10^-15, exit loop
   bc1t expExit

   add.s $f0, $f0, $f7      #add new term to sum
   j summation              #repeat loop

expExit:
  c.eq.s $f12, $f8            #check to see of function parameter is negative
  bc1t expEnd                 #if function parameter is positive, exit normally
  div.s $f0, $f30, $f0         #if function parameter is negative, invert sum
expEnd:
  jr $ra
