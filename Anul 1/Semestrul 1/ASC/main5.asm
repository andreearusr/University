bits 32
global start

extern exit,fopen,fclose,scanf,printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

extern maximul

segment data use32 class=data public 
    sir times 100 dd 0
    
    numar dd 0
    format db "%d",0
    format2 db "%x",0
    contor dd 0
    
    nume_fis db "max.txt",0
    mod_acces db "w",0
    descriptor_fis dd -1

segment code use32 class=code public
start:
   

    mov EDI,sir
    cld 
    
    repeta:
        push dword numar 
        push dword format
        call [scanf]
        add ESP,4*2
        
        mov EAX,[numar]
        cmp EAX,0
        je continua
        
        stosd
        inc dword[contor]
    jmp repeta
    
    cld 
    continua:
    push dword [contor]
    push dword sir
    call maximul
    add ESP,4*2
    
    mov ESI,sir 
    lodsd 
    
    push dword EAX 
    push dword format
    call [printf]
    add ESP,4*2
    

    
    final:
    push dword 0
    call [exit]