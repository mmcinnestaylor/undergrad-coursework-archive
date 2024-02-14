	.text
	ori	$s0,$0,32
	lw	$t1,0($s0)
	lw	$t2,4($s0)
	noop
	and	$s3,$0,15
	sub	$t3,$t1,$t2
	sw	$t3,8($s0)
	andi	$s1,$s0,15
	ori	$t3,$t1,23
	noop
	sub	$s0,$t4,$t5
	halt
	.data
Thing:	.word	12
Whatever:	.word	 25
blue:	.word	19