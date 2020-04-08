#Strimbeanu Luana
#Grupa 143 Semigrupa 2
#15.1.2020
#MARS

.data
	t:.word 2
	n:.word 4
	v:.word 321, 45, 12, 67

.text
j main
eval:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	addi $fp, $sp, 4
	subu $sp, $sp, 4
	sw $ra, 0($sp)
	subu $sp, $sp, 4
	sw $s0, 0($sp)
	subu $sp, $sp, 4
	sw $s1, 0($sp)
	subu $sp, $sp, 4
	sw $s2, 0($sp)
	subu $sp, $sp, 4
	
	lw $s0, 0($fp) #*v
	lw $s1, 4($fp) #n
	lw $s2, 8($fp) #t
	
	li $t2, 0 #i
	li $v0, 0
	
	loop:
		bge $t2, $s1, exit
		
		lw $t1, 0($s0)
		mul $t1, $t1, $s2
		subu $sp, $sp, 4
		sw $t1, 0($sp)
		
		jal cifre_ordonate_desc
		
		addu $sp, $sp, 4
		
		lw $t1, 0($s0)
		div $t3, $t2, 3
		add $t3, $t3, $t1
		mulu $t3, $t3, $v1
		addu $v0, $v0, $t3
		
		addi $t2, $t2, 1
		addi $s0, $s0, 4
		j loop
	
	exit:
		lw $s2, -20($fp)
		lw $s1, -16($fp)
		lw $s0, -12($fp)
		lw $ra, -8($fp)
		lw $fp, -4($fp)
		addu $sp, $sp, 20
	
	jr $ra
	
cifre_ordonate_desc:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	addi $fp, $sp, 4
	subu $sp, $sp, 4
	sw $s0, 0($sp)
	
	lw $s0, 0($fp) #x
	rem $t0, $s0, 10 #last
	div $s0, $s0, 10
	loop2:
		beqz $s0, ok
		rem $t1, $s0, 10
		ble $t1, $t0, neok
		div $s0, $s0, 10
		j loop2
	
	neok:
		li $v1, 0
		j exit2
	
	ok:
		li $v1, 1
	
	exit2:
		
		lw $s0, -8($fp)
		lw $fp, -4($fp)
		addu $sp, $sp, 8
		jr $ra
	

main:
	lw $t0, t
	subu $sp, $sp, 4
	sw $t0, 0($sp)
	
	lw $t0, n
	subu $sp, $sp, 4
	sw $t0, 0($sp)
	
	la $t0, v
	subu $sp, $sp, 4
	sw $t0, 0($sp)
	
	jal eval
	
	addu $sp, $sp, 12
	move $a0, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall