	.text
	ori	$s0,$0,32
	noop
	ori	$s0,$0,32
        lw	$t1,0($s0)
        lw	$t0,4($s0)
        noop
        andi	$s3,$0,15
        sub	$t1,$t1,$t2
        sw	$t1,8($s0)
        andi	$s1,$s0,15
        ori	$t3,$t1,23
        noop
        sub	$s0,$t4,$t5
	sll	$t1,$0,4
	andi	$s3,$0,15
	lw	$t1,0($s0)
	lw	$s0,4($s0)
	noop
LOOP:	andi	$s1,$s0,15
	ori	$t0,$t1,23
	ori	$s0,$0,32
        noop
        ori	$s0,$0,32
        lw	$t1,0($s0)
        lw	$t2,4($t1)
        noop
        andi	$s3,$0,15
        sub	$t1,$t1,$t2
        sw	$t2,8($s0)
        andi	$s1,$s0,15
	sub	$t0,$t1,$t0
	noop
	sub	$s0,$1,$t5
	sll	$t0,$1,4
	noop
	sw	$s1,8($s0)
        noop
LOOP2:	sub	$s3,$s4,$s5
	sub	$s5,$s6,$s3
	add	$0,$s3,$s2
	add	$0,$0,$1
	andi	$0,$0,16
	bne	$0,$s0,LOOP
        noop
	ori	$t0,$t1,12
	ori	$t1,$t0,8
	bne	$t1,$t2,LOOP2
	sll	$t0,$1,4
	sub	$s3,$s4,$s5
        sub	$s5,$s6,$s3
LOOP3:	add	$0,$s3,$s2
        add	$0,$0,$1
        andi	$0,$0,16
        bne	$0,$s0,LOOP
        noop
        ori	$t0,$t1,12
        ori	$t1,$t0,8
        bne	$t1,$t2,LOOP2
LOOP4:	sll	$t0,$1,4
        andi	$t1,$s0,16
        lw	$t1,8($s0)
        sw	$t1,16($s0)
        and	$t0,$t0,$s0
	andi	$t1,$s0,16
	lw	$t1,8($s0)
	bne	$0,$s0,EXIT
	sw	$t1,16($s0)
EXIT:	and	$t0,$t0,$s0
	halt
	.data
Thing:	.word	12
Whatever:	.word	 25
hello:	.word	15
its:	.word 	40
me:	.word	25
im:	.word	11
adele:	.word	80
is:	.word	90
it:	.word	30
i:	.word	45
youre:	.word	99
looking:	.word	55
for:	.word	94
blue:	.word	19
