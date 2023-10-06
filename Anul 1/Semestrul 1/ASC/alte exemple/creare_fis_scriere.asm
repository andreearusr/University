bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf,fopen,fclose,fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        nume_fisier times 31 db 0
        mod_acces db "w",0
        
        descriptor_fis dd -1
        text times 121 db 0
        mesajfisier db "numele fisierului= ",0
        mesajtext db "text= ",0
        format db "%s",0

; our code starts here
segment code use32 class=code
    start:
        ; Sa se citeasca de la tastatura un nume de fisier si un text. Sa se creeze un fisier cu numele dat in directorul
        ; curent si sa se scrie textul in acel fisier. Observatii: Numele de fisier este de maxim 30 de caractere.
        ; textul de maxim 120 de caractere
    
        push dword mesajfisier
        call [printf]    ; afiseaza "numele fisierului= "
        add ESP,4*1 
        
        push dword nume_fisier
        push dword format   ; citeste numele fisierului de tip string
        call [scanf]
        add ESP,4*2
        
        push dword mesajtext
        call[printf]    ; afiseaza "text= "
        add ESP,4*1
        
        push dword text
        push dword format
        call [scanf]     ; citeste textul de tip string
        add ESP,4*2
        
        ; apelam fopen(nume_fisier,mod_acces) pt a crea fisierul 
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add ESP,4*2
        
        mov [descriptor_fis],EAX
        
        cmp EAX,0
        je final
        
        ;scriem textul in fisierul deschis cu fctia fprintf(descriptor_fis,text)
        push dword text
        push dword [descriptor_fis]
        call [fprintf]
        add ESP,4*2
        
        ;inchidem fisierul fclose(descriptor_fis)
        push dword [descriptor_fis]
        call[fclose]
        add ESP, 4*1
        
        final:
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
