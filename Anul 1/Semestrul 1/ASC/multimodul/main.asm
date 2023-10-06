bits 32 
global start        
;Sa se citeasca de la tastatura un sir de numere in baza 10 fara semn
;Sa se det val minima din sir si sa se afiseze in fisierul min.txt,in baza 16

extern exit,scanf,fopen,fclose,fprintf               
import exit msvcrt.dll    
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll                      

extern modul 

segment data use32 class=data
        n dd 0
        x dd 0FFFFFFFFh
        format_int db "%d",0
        format_hex db "%x",0
        mod_acces db "w",0
        nume_fisier db "min.txt",0
        descriptor_fis dd 0
        spatiu db " ",0

segment code use32 public code 
    start:
        
        repeta:
            pushad
            
            push dword n 
            push dword format_int
            call [scanf]
            add ESP,4*2
            
            popad
            
            cmp dword[n],0   ; daca n=0
            je printare      ;iesire din citire
            
            push dword [x]
            push dword [n]
            call modul 
            add ESP,4*2 
            
            mov [x],EAX
        jmp repeta
        
        
        printare:
            push dword mod_acces
            push dword nume_fisier
            call [fopen]
            add ESP,4*2
            
            cmp EAX,0
            jz final
            
            mov [descriptor_fis],EAX 
            
            push dword [x]
            push dword format_hex
            push dword [descriptor_fis]
            call [fprintf]
            add ESP,4*3
            
            inchide_fisier:
                push dword [descriptor_fis]
                call [fclose]
                add ESP,4
            
        final:

        push    dword 0      
        call    [exit]      
