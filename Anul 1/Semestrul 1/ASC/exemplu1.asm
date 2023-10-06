bits 32

global start
extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll


segment data use32 class=data
    a dw 2150
    b db 6
    
    mesaj1 db "Catul= ",0
    mesaj2 db "Restul= ",0
    
    format db "%u ",0
      

segment code use32 class=code
start: 
    
    mov AX, word[a]
    mov DX,0   ;DX:AX=a 
    
    mov BL,byte[b]
    mov BH,0   ;BX=b 
    
    div BX   ;AX cat   DX rest

    mov BX,AX
    mov EAX,0
    mov AX,BX  ;EAX catul
    
    pushad 
    push dword mesaj1 
    call [printf]
    add esp,4*1
    popad 
    
    push EDX
    push dword EAX
    push dword format
    call [printf]
    add esp,4*2
    pop EDX 
    
    mov BX,DX 
    mov EAX,0
    mov AX,BX  ;EAX catul
    
    pushad 
    push dword mesaj2 
    call [printf]
    add esp,4*1
    popad 
    
    push dword EAX
    push dword format
    call [printf]
    add esp,4*2
    

    push dword 0
    call [exit]