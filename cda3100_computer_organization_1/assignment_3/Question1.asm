.text
.globl main
main: ori $t0, $0, 28
	and $t1, $t1, $0
	and $t2, $t2, $0
	and $t3, $t3, $0
	and $t4, $t4, $0
LOOP: beq $t4, 32, EXIT
	addi $t4, $t4, 1                #increment loop counter by 1
	andi $t2, $t0, 1                #check if the last digit in t0 is 1, store result in t2
	bne $t2, $0, L1                #if t2 is 1, jump to L1
	sub $t3, $t3, $t3              #reset 1's counter is a 0 is encountered
	srl $t0, $t0, 1
	j LOOP
L1:      addi $t3, $t3, 1
	beq $t3, 3, L2                  #if 1's counter is 3, jump to L2
	srl $t0, $t0, 1
	j LOOP
L2:      addi $t1, $t1, 1                #if 111 found in string, set t1 to 1
EXIT:
DONE: li $v0, 10
	syscall
