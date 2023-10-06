bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,printf,fscanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fscanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        nume_fisier db "incercare.txt",0
        mod_acces db "r",0
        descriptor_fis dd -1
        text times 50 db 0
        
        contor dd 0
        format db "sirul este:%s ",0
        format1 db "%d ",0
        sir_initial times 100 db 0

; our code starts here
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
        mov EDI, sir_initial
        
        bucla:
       
            push dword text
            push format1
            push dword [descriptor_fis] 
            call [fscanf]                   
            add ESP, 4*3
            
            cmp EAX,0
            je done
              
            mov EAX,[text]
            
            cld
            stosd
            
            
            inc dword[contor]
            
            push dword EAX
            push dword format1
            call [printf]
            add ESP,4*2
            
            cmp dword[contor],4
        jb bucla
            
        
        done:
        
        ;fclose(descriptor_fis)
        push dword[descriptor_fis]
        call [fclose]
        add ESP, 4*1
        
        final :  
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
