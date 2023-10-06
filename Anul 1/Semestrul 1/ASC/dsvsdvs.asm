bits 32

global start
extern exit,printf,scanf,fopen,fclose,fprintf,fscanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll

segment data use32 class=data

    nume times 150 db 0

    mesaj1 db "Dati numele fisierului: ",0,10

    format db "%s ",0
    format2 db "%s",0

    nume_fisier db "simulare5.txt",0
    mod_acces db "r",0
    descriptor_fis dd -1
    
    max_cuv equ 100
    cuvant times 50 db 0
    contor dd 0


segment code use32 class=code
start:
    
    push dword nume 
    push dword format2
    call [scanf]
    add ESP,4*2
    
    
    push dword mod_acces
    push dword nume
    call [fopen]
    add ESP,4*2
    
    cmp EAX,0
    je final
    mov [descriptor_fis],EAX
    
    
    mov ECX, max_cuv
   
    mov EBX,0
    
    bucla:
        
        push dword cuvant
        push dword format
        push dword [descriptor_fis]
        call [fscanf]
        add ESP,4*3
        
        
        cmp EAX,1
        jne cleanup
        
        push ecx
        
        push dword cuvant
        push dword format
        call [printf]
        add ESP,4*2
        
        pop ecx 

        inc EBX 
    
    loop bucla
    
    
    cleanup:
    mov dword[contor],EBX
    
    push dword [descriptor_fis]
    call [fclose]
    add ESP,4*1
    

    final:
   
    push dword 0
    call [exit]