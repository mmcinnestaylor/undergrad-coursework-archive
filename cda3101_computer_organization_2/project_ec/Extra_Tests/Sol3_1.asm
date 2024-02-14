	.text
	ori	$s0,$0,32
	noop
	and	$s3,$0,15
	lw	$t1,0($s0)
	lw	$t2,4($s0)
	andi	$s1,$s0,15
	ori	$t4,$t1,23
	sub	$t3,$t1,$t2
	noop
	sub	$s0,$t4,$t5
	sw	$t3,8($s0)
	halt
	.data
Thing:	.word	12
Whatever:	.word	 25
blue:	.word	19