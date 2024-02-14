.data

A:  .word 90, 2, 93, 66, 8, 120, 121, 11, 33, 9

.text
.globl main

main: la $s0, A
      li $s1, 10

      andi $s2, 0
      andi $t0, 0
      andi $t1, 0
      andi $t2, 0
      andi $t3, 0
      andi $t4, 0
      andi $t5, 0

LOOP: bne $s1, $t0, L1     #checks is entire array has been checked

      blt $t2, $t3, SUB

      sub $a0, $t2, $t3    #stores subtraction value in a0
      j EXIT

SUB:  sub $a0, $t3, $t2    #alternate subtraction to avoid a negative result
      j EXIT

L1:   add $s2, $s0, $t4
      lw $t1, 0($s2)
      add $t0, $t0, 1      #increment loop counter
      add $t4, $t4, 4      #increment offset
      bgt $t1, $t2, L2     #check for new greatest value
      bgt $t1, $t3, L3     #check for new greatest value
      j LOOP

L2:   add $t3, $0, $t2
      add $t2, $0, $t1
      j LOOP

L3:   add $t3, $0, $t1
      j LOOP

EXIT:
DONE: li $v0, 10
      syscall
