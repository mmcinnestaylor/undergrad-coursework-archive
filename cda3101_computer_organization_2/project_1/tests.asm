      .text
main: add $t0,$t1,$t2
      la  $t1,done
_a1:  addi  $t3,$t4,10000
      addi  $t4,$t3,-999999
loop: la  $t2,main
      ori $t7,$t7,-88
_b2:  nor $t6,$t7,$0
      bne $t3,$s3,_a1
data: j path
      lw  $t3,-4($s2)
      bne $t6,$s5,alert
fun99:  ori $s0,$s1,15937
      sll $s7,$t1,13
gasm:  sw  $s2,64($s3)
n00b: la  $t6,nearly
      sw  $s6,-32($s7)
meh:  bne $s1,$t3,100
dave: lui $s3,1962
      addi  $s1,$t7,493721
      j turing
      ori $s4,$t1,-3876529
100:  lw  $s4,-16($s5)
      lw  $t0,48($s0)
      nor $s5,$t2,$s6
nerd: bne $t4,$s4,gasm
      ori $t1,$s6,49721
turing: addi  $s7,$s7,-0825028
      add $t6,$s6,$t7
      lui $t3,249813
machine:  sll $t1,s5,27
      lui $s6,$t1,-696969
chappelle:  lui $t1,-666666
life: sw  $t5,-400($t1)
path: j data
alert:  lw  $t4,24($s7)
      sw  $s4,4000($t2)
      la  $t1,loop
      j 100
      .data
nearly: .word 4
      .space 100000
      .word 69
done: .space 500
