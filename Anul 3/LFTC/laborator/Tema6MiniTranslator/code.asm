bits 32
global start
extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
in_format db "%d", 0
out_format db "%d ", 0
a dd 0
b dd 0
c dd 0

segment code use32 class=code
start:
push dword a
push dword in_format
call [scanf]
add esp, 4*2
push dword b
push dword in_format
call [scanf]
add esp, 4*2
mov ebx, [a]
mov eax, ebx
mov ebx, 2
mov edx, 0
div ebx
mov ebx, eax
mov [a], ebx
push dword [a]
push dword out_format
call [printf]
add esp, 4*2
mov ebx, [b]
mov eax, ebx
mov ebx, 5
mov edx, 0
div ebx
mov ebx, eax
mov [b], ebx
push dword [b]
push dword out_format
call [printf]
add esp, 4*2
mov ebx, [b]
mov eax, ebx
mov ebx, [a]
mul ebx
mov ebx, eax
add ebx, 1
sub ebx, 4
add ebx, 6
mov [c], ebx
mov ebx, [c]
sub ebx, 3
mov [c], ebx
push dword [c]
push dword out_format
call [printf]
add esp, 4*2

push dword 0
call [exit]
                                                                                              