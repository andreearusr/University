bits 32 

global start
extern exit,printf,scanf,fprintf,fopen,fclose
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data

    sir times 100 db 0
    nr dd 0
    format db "%d ",0
    contor dd 0
    
    nume_fis db "simulare4.txt",0
    mod_acces db "w",0
    descriptor_fis dd -1

; Sa se citeasca de la tastatura mai multe numere pana la citirea valorii 0. Sa se scrie intr-un fisier, separate de spatii, doar acele numere
;  pozitive care au numar par de biti 1(cu valoarea1)
segment code use32 class=code
    start:
    
    push dword mod_acces
    push dword nume_fis
    call [fopen]
    add ESP,4*2
    
    cmp EAX,0
    je final 
    
    mov [descriptor_fis],EAX
    
    mov EDI,sir
    cld
    mov EAX,0
    
    repeta:

        push dword nr
        push dword format
        call [scanf]
        add ESP,4*2
        
        mov EAX,dword[nr]
        cmp EAX,0
        je transforma 
        
        STOSD
        inc dword[contor]
        
    jmp repeta
    
    transforma:
    mov ESI,sir
    cld
    mov EAX,0
    mov ECX,dword[contor]
    
    bucla
        LODSD    ;EAX<- numarul curent din sir
        cmp EAX,0
        ja verificare 
        jmp aici
        
        verificare:
            jp afisare
            jnp aici 
            
            afisare:
            pushad
                push dword EAX
                push dword format
                push dword [descriptor_fis]
                call [fprintf]
                add ESP,4*3
            popad
        aici:
    loop bucla
        
    final:
        push dword [descriptor_fis]
        call [fclose]
        add ESP,4*1
    
    
    push dword 0
    call [exit]
