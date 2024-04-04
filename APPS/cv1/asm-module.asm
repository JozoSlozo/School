;***************************************************************************
;
; Program for education in subject "Assembly Languages" and "APPS"
; petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
;
; Empty project
;
;***************************************************************************

    bits 64

    section .data

    extern g_int_x
    extern g_int_y
    extern g_char_arr
    extern g_char_str
    extern g_long_arr


;***************************************************************************

    section .text

    global set_x_y
set_x_y:
    enter 0,0
    mov dword [ g_int_x ], -654321
    mov qword [ g_int_y ], 0x53705041
    leave
    ret

    global set_char_arr
set_char_arr:
    enter 0,0
    mov  eax, dword [g_int_y]
    mov dword [g_char_arr], eax
    leave
    ret

    global change_char
change_char:
    enter 0,0
    mov byte [g_char_str + 8], 'A'
    mov byte [g_char_str + 9], 'S'
    mov byte [g_char_str + 10], 'M'
    leave
    ret

    global set_long_arr
set_long_arr:
    enter 0,0
    movsx  rax, dword [g_int_x]
    mov qword [g_long_arr], rax
    mov  rax, qword [g_int_y]
    mov qword [g_long_arr+8], rax
    leave
    ret