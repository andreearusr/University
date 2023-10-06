bits 32 

global start        


extern exit,scanf,fopen,fclose,fprintf,printf               
import exit msvcrt.dll    
import scanf msvcrt.dll                          
import fopen msvcrt.dll  
import fclose msvcrt.dll          
import fprintf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data

    
    sir  times 100 dd 0
    numar dd 0
    format db "%d ",0
    contor dd 0
    
    nume_fis db "1-impar_neg.txt",0
    mod_acces db "w",0
    descriptor_fis dd -1
    
; Scrie un program care citeste de la tast mai multe nr intregi cu semn pana ce se introduce valoarea 0. Stocheaza nr-le intr-o variabila.
; Determina nr-le negative care contin un nr impar de biti care au valoarea 1. Creeaza un fisier text numit "1-impar_neg.txt" si scrie
; in acest fisier nr-le intregi determinate anterior.
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
       bucla:
 
            push dword numar
            push dword format
            call [scanf]
            add ESP, 4*2

            mov EAX,dword[numar]
            cmp EAX,0
            je continuare
            
            STOSD
            inc dword[contor]

        jmp bucla
           
         
        continuare:
        mov ECX, dword [contor]
        
        
        push dword ECX
        push dword format
        call [printf]
        add ESP,4*2
        
        
        mov ECX, dword[contor]
        mov ESI,sir
        cld
        
        verificare:
            mov EAX,0
            LODSD
            cmp EAX,0
            jl continua
            jmp aici
            
            continua:
                jnp continua1
                jp aici
                
                continua1:
                pushad

                push dword EAX 
                push dword format
                push dword [descriptor_fis]
                call [fprintf]
                add ESP,4*3
                popad
                
            aici:
        
        loop verificare 
        
   
        final:
            push dword [descriptor_fis]
            call [fclose]
            add ESP,4*1
        
        push    dword 0    
        call    [exit]      
