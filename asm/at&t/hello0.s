# The data section is where all data is defined before compilation.
.section .data
        # define a non null terminated string "Hello, World\n", called text
        text : .string "Hello, world!\n"

# The text section is where the actual code goes.
.section .text
        .global _start

_start:
        movq $1, %rax        # -+
        movq $1, %rdi        #  |
        movq $text, %rsi     #  | sys_write(1, text, 14)
        movq $14, %rdx       #  |
        syscall              # -+

        movq $60, %rax       # -+
        movq $0, %rdi        #  | sys_exit(0)
        syscall              # -+
