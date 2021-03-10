f:
addiu $sp, $sp, -64
nop
sw $ra, 60($sp)
nop
sw $fp, 56($sp)
nop
sw $s0, 4($sp)
nop
sw $s1, 8($sp)
nop
sw $s2, 12($sp)
nop
sw $s3, 16($sp)
nop
sw $s4, 20($sp)
nop
sw $s5, 24($sp)
nop
sw $s6, 28($sp)
nop
sw $s7, 32($sp)
nop
move $fp, $sp
nop
sw $a0, 36($sp)
nop
sw $a1, 40($sp)
nop
sw $a2, 44($sp)
nop
sw $a3, 48($sp)
move $v0, $s5
nop
lw $s0, 4($sp)
nop
lw $s1, 8($sp)
nop
lw $s2, 12($sp)
nop
lw $s3, 16($sp)
nop
lw $s4, 20($sp)
nop
lw $s5, 24($sp)
nop
lw $s6, 28($sp)
nop
lw $s7, 32($sp)
nop
lw $ra, 60($sp)
nop
lw $fp, 56($sp)
nop
move $sp, $fp
jr $ra
nop
.global f

