# the CPU (even an x86_64) starts in 16-bit mode, we need to produce 16-bit
# (8086) asm
.code16

.text
	.globl _start
_start:
	# load the string address in %si and call our "puts" routine
	leaw s1, %si
	call puts

idle:
	# then run an infinite loop to wait
	jmp idle

# define a routine that will print a string whose address is places in %si
puts:
	lodsb # %al = *(%si++)
	test %al, %al
	jz puts_end

	# print the character in %al to the screen:
	# - routine no. 0x0e ("Write Character in TTY Mode"), in %ah
	# - interrupt vector no. 0x10
	movb $0x0e, %ah
	int  $0x10
	