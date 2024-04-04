bits 64
section .data

section .text

global strcat
strcat:
    enter 0,0

    mov rax, 0 ; count = 0
    mov rcx, rdx ; rcx = count
    mov rsi, rdi ; rsi = string
    mov rbx, 0 ; i = 0
    mov r8, 0 ; is first
    mov ebx, 0 ; dword i = 0

.back:
    cmp byte [rsi], 0
    je .end

    cmp byte [rsi], sil
    je .stejne

    inc ebx
    inc rsi
    jmp .back

.stejne:
    inc rax

    cmp r8, 0
    jmp .first

    inc ebx
    inc rsi
    jmp .back

.first:
    mov eax, ebx
    
    inc ebx
    inc rsi
    jmp .back
.end:
    mov [rcx], rax
    leave
    ret

global str2int
str2int:
    enter 0,0

    mov rax, 0
    mov rsi, rdi
    mov rcx, 0

.back:
    cmp byte [rsi], 0 
    je .end

    movzx rdx, byte [rsi]
    sub rdx, '0' 
    imul rax, 10
    add rax, rdx

    inc rsi
    jmp .back

.end:
    leave
    ret
