bits 32

global start

extern exit,fopen,fread,fclose,printf ,scanf            

import exit msvcrt.dll    
import fopen msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
    nume_fisier db "f1.txt",0
    mod_acces db "r",0
    descriptor_fis dd -1
    text db 0
    
    max equ 100
    sir times max db 0 
    n dd 0
    nr dd 0
    
    mesaj db "  Lungimea sirului nu este cuprinsa intre 0 si 16!",10,0
    mesaj2 db "Introduceti un numar intre 1 si 16:",0
    format_eroare db "%s",0
    format db "%d",0
    


segment code use32 class=code
start:
    ;fopen(nume_fisier,mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call[fopen]
        add ESP, 4*2
        
        cmp EAX,0
        je final
        
        mov [descriptor_fis],EAX
        mov ESI,sir 
        mov ECX,max
        cld 
        
        bucla:
        
            push dword [descriptor_fis]
            push dword 1
            push dword 1
            push dword text
            call [fread]
            add ESP,4*4
            
            cmp EAX,1
            jne cleanup
            
            mov EAX,[text]
            stosd
            
            inc dword[n]
            
        loop bucla 
        
        cleanup:
        
        ;fclose(descriptor_fis)
        push dword[descriptor_fis]
        call [fclose]
        add ESP, 4*1
        
        mov ECX,[n]
        cmp ECX,1
        jb eroare
        
        cmp ECX,16
        ja eroare
        
        push dword mesaj2
        push dword format_eroare
        call[printf]
        add ESP,4*2
            
        push dword nr
        push dword format 
        call [scanf]
        add ESP,4*2
        
        mov ECX,[n]
        jecxz final
        
        mov ESI,sir
        cld 

        cont:
            push ECX

            mov EAX,0
            lodsd
            
            push dword EAX 
            push dword format1
            call [printf]
            add ESP,4*2
            
            pop ECX 
            
        loop cont
        
        eroare:
            push dword mesaj
            push dword format_eroare
            call[printf]
            add ESP,4*2
            
        
        final:
        push dword 0
        call [exit]