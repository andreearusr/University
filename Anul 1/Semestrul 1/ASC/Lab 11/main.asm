bits 32

global start      

extern exit,fopen,fread,fclose,printf,fscanf               
extern dest

import exit msvcrt.dll    
import fopen msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll


; pb 10: Se citeste din fisierul "numere.txt" un sir de numere. Sa se determine sirul destinatie D care contine numerele
; din sirul initial cu valorile dublate, dar in ordine inversa din sirul initial. Sa se afiseze sirul obtinut pe ecran
segment data use32 class=data public
        nume_fisier db "numere.txt",0
        mod_acces db "r",0
        descriptor_fis dd -1
        numar dd 0

        nr_citite dd 0 
        max equ 100
        
        sir times max db 0
        sir_final times max db 0

        format db "%d ",0
    

segment code use32 class=code public 
    start:
    
        ;fopen(nume_fisier,mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call[fopen]
        add ESP, 4*2
        
        cmp EAX,0
        je final
        
        mov [descriptor_fis],EAX
        
        mov ECX,max
        mov EDI, sir
        cld
  
        bucla:

            ; fscanf(descriptor_fis, format, numar)
            push dword numar
            push dword format
            push dword [descriptor_fis] 
            call [fscanf]                   
            add ESP, 4*3
            
            cmp EAX,1
            jne cleanup
            
            mov EAX,[numar]
            stosd 
            
            inc dword [nr_citite] 

        loop bucla

        cleanup:
        
        ;fclose(descriptor_fis)
        push dword[descriptor_fis]
        call [fclose]
        add ESP, 4*1
        
        
        push dword sir 
        push dword sir_final
        push dword [nr_citite]
        call dest
        add ESP,4*3
        

        mov ECX,[nr_citite]
        jecxz final

        
        mov ESI,sir_final
        cld 

        cont:
            push ECX

            mov EAX,0
            lodsd
            
            push dword EAX 
            push dword format
            call [printf]
            add ESP,4*2
            
            pop ECX 
            
        loop cont 

        
        final:
        push    dword 0      
        call    [exit]       

