; The data section is where all data is defined before compilation.
section .data
        ; define a non null terminated string "Hello, World\n", called text
        ; 10 is the ASCII character '\n'
        ; db stands for "define bytes"
        text db "Hello, World!",10

; The text section is where the actual code goes.
section .text
        global _start

_start:
        mov rax, 1        ; -+
        mov rdi, 1        ;  |
        mov rsi, text     ;  | sys_write(1, text, 14)
        mov rdx, 14       ;  |
        syscall           ; -+

        mov rax, 60       ; -+
        mov rdi, 0        ;  | sys_exit(0)
        syscall           ; -+
