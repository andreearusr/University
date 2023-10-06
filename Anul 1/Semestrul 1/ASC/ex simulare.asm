bits 32

global start
extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll

; Se citeste un sir de dublucuvinte si un caracter. Sa se afiseze pe ecran cuvintele ai caror octeti superiori sunt egali cu
; codul ascii al caracterului citit

segment data use32 class=data

    sir dd 0ABCD0123h,56781234h
    l equ ($-sir)/2 
    caracter db 'p'
    
    sir_f times l dw 0
    format db "%x",0
    
segment code use32 class=code   
    start:
    
    mov ECX,l
    mov ESI,sir 
    mov EDI,sir_f
    mov EBX,0
    cld 
    
    repeta:
        LODSW
        cmp AH, [caracter]
        jne sari
        STOSW
        inc EBX 
        
        sari:
        
    loop repeta
    
    mov ECX,EBX 
    cld 
    mov ESI,sir_f
    
    repeta1:
        mov EAX,0
        LODSW 
        
        pushad
        push dword EAX 
        push dword format 
        call [printf]
        add ESP,4*2
        
        popad
        
    loop repeta1
        

    push dword 0
    call [exit]
    
    
    