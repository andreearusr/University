bits 32

global start
extern exit,printf,scanf,fopen,fclose,fprintf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    n dd 0
    a dd 0
    suma dd 0
    contor dd 0

    mesaj db "n= ",0,10
    mesaj2 db "nr= ",0,10
    format db "%u ",0
    
    nume_fis db "simulare3.txt",0
    mod_acces db "w",0
    descriptor_fis dd -1
    
; Sa se citeasca de la tastatura un nr N reprezentat pe un octet si apoi N nr intregi reprezentate pe un octet
; Programul va calcula suma acestor numere (S<256) si va scrie intr-un fisier pctetii de la 0 pana la S
segment code use32 class=code
    start:
    
    push dword mod_acces
    push dword nume_fis
    call [fopen]
    add ESP,4*2
    
    cmp EAX,0
    je final
    
    mov [descriptor_fis],EAX
    
    push dword mesaj
    call [printf]
    add ESP,4*1
    
    push dword n
    push dword format
    call [scanf]
    add ESP,4*2
    
    
    mov ECX,0
    mov CL,[n]
    
    repeta:
        pushad
        
        push dword mesaj2
        call [printf]
        add ESP,4*1
        
        push dword a
        push dword format
        call [scanf]
        add ESP,4*2
        
        mov EAX,[a]
        add word[suma],AX
        
        popad
        
    loop repeta 
   
    push dword [suma]
    push dword format
    call [printf]
    add ESP,4*2
    
    mov ECX,0
    mov CX,[suma]
    mov word[contor],0
    bucla:
        pushad
        mov EAX,0
        mov AX,word[contor]
        
        push dword EAX
        push dword format
        push dword [descriptor_fis]
        call [fprintf]
        add ESP,4*3
        popad
        
        inc word[contor] 
        
    loop bucla
    

    push dword [descriptor_fis]
    call [fclose]
    add ESP,4*1
    
    final:
    
    push dword 0
    call [exit]
    
    