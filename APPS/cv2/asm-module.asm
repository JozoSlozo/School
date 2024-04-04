bits 64

section .data
    extern data_x
    extern count
    extern result_num
    extern iterations
    extern text
    extern from
    extern replace_to
section .text

    global count_ones
count_ones:
    enter 0,0

    mov eax, 0 ;i = 0
    mov edx, 1
.loop:
    cmp eax, 32
    jnl .end

    mov ecx, [data_x]
    shl edx, 1
    and ecx, edx
    jg .vetsi
    inc eax    
    jmp .loop

.vetsi:
    inc dword [count]
    inc eax
    jmp .loop
.end:
    leave
    ret

    global fibb
fibb:
    enter 0,0
    mov eax, [iterations]
    mov ebx, 0 ;prev
    mov ecx, 1 ;next
.loop:
    dec eax
    
    mov edx, ecx
    add edx, ebx
    mov ebx, ecx
    mov ecx, edx

    cmp eax, 0
    jbe .end

    jmp .loop
.end
    mov [result_num], ecx
    leave
    ret

    global replace_char
replace_char:
    enter 0,0

    mov eax, 0 ;i = 0
.loop:
    cmp eax, 8
    jnl .end
    
    mov ah, byte[text + eax]
    cmp byte [from], ah
    je .stejne

    inc eax
    jmp .loop

.stejne:
    mov al, [replace_to]
    mov byte [text + eax], al
    inc eax
    jmp .loop

.end:
    leave
    ret

