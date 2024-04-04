    bits 64

    section .data

;***************************************************************************

    section .text

global fill_pyramid_numbers
fill_pyramid_numbers:
    enter 0,0
    mov rbx, 1
    mov r8, 0
    movsx rcx, esi
    inc rcx
.main:
    cmp rbx, rcx
    je .end
    mov rax, rbx
    mul rbx

    add r8, rax

    dec rbx
    mov qword [rdi + rbx * 8], r8
    
    add rbx, 2
    jmp .main
.end:
    leave
    ret

global multiples
multiples:
    enter 0,0
    mov r8, 0  ; r8 = pocet delitelu
    mov rbx, 0  ; i = 0
    movsx rcx, esi ; rcx = len
    mov r9, rdx ;r9 = factor
.main:
    cmp rbx, rcx
    je .end

    mov rdx, 0
    mov rax, qword [rdi + rbx * 8]
    div r9

    cmp rdx, 0
    je .stejne

    mov rax, r9
    mul qword [rdi + rbx * 8]
    mov qword [rdi + rbx * 8], rax

    inc rbx
    jmp .main

.stejne:
    inc r8
    inc rbx
    jmp .main
.end:
    mov rax, r8
    leave
    ret

global factorial
factorial:
    enter 0,0

    mov ebx, 0 ; i = 0
.main:
    cmp ebx, esi
    jge .end

    mov ecx, 1 ; l = 0
    mov eax, 1
    mov edx, 0
.fact:
    movsx rbx, ebx
    cmp ecx, dword [rdi + rbx * 4]
    jge .factend

    mul ecx
    inc ecx
    jmp .fact

.factend:
    movsx rbx, ebx
    mov dword [rdi + rbx * 4], eax
    inc ebx
    jmp .main
.end:
    mov eax, 10
    leave
    ret