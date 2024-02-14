#This is the main program for problem 1 in Assignment 7 and placeholders for your find() and match() functions
#Only fill out those placeholders with your code. Please do NOT write your own main function﻿﻿﻿﻿﻿﻿﻿﻿﻿

	.data
list: .word 193, 77, 31, 22, 51, 17, 16, 3, 0, 359, 67, 82, 9, 17, 1 #this is the list to check against
check_values: .word 13, 79, 12, 5, 0
newline: .asciiz "\n"
whitespace: .asciiz " "


	.text
	.globl main
main:
	la $s0, list			#load address of list
	la $s1, check_values	#load address of check_values
	li $t0, 0				#counter
	li $s2, 5				#s2=length of check_values[]
	ori $a0, $s0, 0			#a0=starting address of list. This does NOT change
	ori $a2, $0, 15			#a2=length of list. This does NOT change either
loop:
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	lw $t2, 0($t1)
	ori $a1, $t2, 0			#a1=integer to check
	addi $sp, $sp, -12		#make space on stack to hold three temporary registers
	sw $t0, 0($sp)			#store temporary registers on stack
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	jal find				#call function
	lw $t2, 8($sp)			#restore temporary registers
	lw $t1, 4($sp)
	lw $t0, 0($sp)
	addi $sp,$sp,12			#restore stack pointer
	addi $t0, $t0, 1		#increment counter to iterate through loop
	bne $t0, $s2, loop
exit:
	li $v0, 10
	syscall

find:
	addi $sp, $sp, -8					#push stack pointer down
	sw $s5, 4($sp)						#store s5 on stack
	sw $a0, 0($sp)						#store starting address of array on stack
	and $s5, $s5, $0					#set s5 to 0, acts as loop counter

findloop:
	beq $s5, $a2, findexit		#if counter = array size, exit function

	addi $sp, $sp, -8					#push stack pointer down
	sw $ra, 4($sp)						#push return address onto stack
	sw $a0, 0($sp)						#push current array index address onto stack

	lw $a0, 0($a0)						#load array value into a0
	jal match
	lw $ra, 4($sp)						#load return address back into ra

	bne $v0, 1, nomatch				#if match returns false, skip output
	syscall										#if there is a match, print array value
	addi $v0, $0, 4						#change value of v0 in order to print ws char
	la $a0, whitespace				#set a0 to address of ws char
	syscall										#print ws char

nomatch:
	lw $a0, 0($sp)						#load array address back into a0
	addi $sp, $sp, 8					#push stack up

	addi $s5, $s5, 1					#increment s5 by 1
	addi $a0, $a0, 4					#move array address in a0 to next index
	j findloop

findexit:
	lw $s5, 4($sp)						#load original value of s5 into s5
	lw $a0, 0($sp)						#load original array address into a0
	addi $sp, $sp, 8					#push stack up
	jr $ra

match:
	li $v0, 0

	bgt $a0, $a1, a0Greater

	srl $t4, $a1, 1
	bgt $a0, $t4, matchExit
	j nomatchexit

a0Greater:
	srl $t4, $a0, 1
	bgt $a1, $t4, matchExit
	j nomatchexit

matchExit:
	li $v0, 1
nomatchexit:
	jr $ra
