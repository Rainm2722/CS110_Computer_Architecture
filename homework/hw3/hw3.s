# `void exit(int);` system call
	.text
exit:
	mv	a1, a0
	li	a0, 17
	ecall
# entry point
	.globl  main
main:
	la  a0, input_inorder	# a0 = &input_inorder
	la  a1, input_postorder	# a1 = &input_postorder
	la  t1, input_size		
	lw  a2, 0(t1)			# a2 = input_size
	jal  ra, build_tree		# build_tree(a0, a1, a2)
# exit(0)
	li	a0, 0
	call	exit

build_tree:
	addi  sp, sp, -20	# get stack space
	sw  ra, 16(sp)	# save ra
	sw  s4, 0(sp)	# save s4
	sw  s3, 4(sp)	# save s3
	sw  s2, 8(sp)	# save s2
	sw  s1, 12(sp)	# save s1
	beq  a2, x0, build_exit	# check size == 0
	li  t0, 4	# t0 = 4
	mul  t0, t0, a2		# t0 = 4 * size
	addi  t0, t0, -4	# t0 = t0 - 4	
	add  t1, a1, t0		# t1 = &input_postorder + 4*(size-1)
	mv  t0, a0	# t0 = &input_inorder
	mv  t3, x0	# t3 = 0 (new_size)
	lw  t5, 0(t1)	# t5 = *t1
loop:
	lw  t6, 0(t0)	# t6 = *t0
	beq   t5, t6, end_loop
	addi  t0, t0, 4	# t0 = t0 + 4
	addi  t3, t3, 1 # t3 = t3 + 1
	jal  x0, loop 	# loop
end_loop:
	addi  s1, t0, 4	# save t0+4 in s1
	mv  s2, a1	# save a1 
	mv  s3, a2	# save a2 (size)
	mv  s4, t3	# save new_size
	mv  t4, a0	# t4 = a0
	
	addi  a0, x0, 1
	add  a1, x0, t5
	ecall	# print *t1
	addi  a0, x0, 11
	addi  a1, x0, ' '
	ecall	# print ' '

	mv  a0, t4	# a0 = t4 
	mv  a1, s2	# restore a1
	add  a2, t3, x0	# a2 = new_size
	jal  ra, build_tree # build_tree(&inorder, &postorder, new_size)

	mv  a0, s1	# a0 = t0 + 4
	li  t2, 4 # t2 = 4
	mul  t2, t2, s4 # t2 = t3 * 4
	add  a1, s2, t2 # a1 = &postorder + new size
	sub  a2, s3, s4 # a2 = size - new_size
	addi  a2, a2, -1 # a2 = a2 - 1
	jal  ra, build_tree # build_tree(a0, a1, a2)

build_exit:
	lw  s4, 0(sp)	# restore s4
	lw  s3, 4(sp)	# restore s3
	lw  s2, 8(sp)	# restore s2
	lw  s1, 12(sp)	# restore s1
	lw  ra, 16(sp)	# restore ra
	addi  sp, sp, 20	# restore stack pointer
	jr  ra	# return
