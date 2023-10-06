bits 32 
global start        

extern exit,fopen,fprintf,fclose               
import exit msvcrt.dll    
import fopen msvcrt.dll 
import fprintf msvcrt.dll 
import fclose msvcrt.dll 

segment data use32 class=data
    ; Se dau un nume de fisier si un text. Textul contine litere mici,litere mari,cifre si caractere speciale.
    ; Sa se transforme toate literele mari din textul dat in litere mici. Se creeaza un fisier cu numele dat si se
    ; scrie textul obtinut in fisier 
    
    nume_fisier db "transformare.txt",0
    descriptor_fis dd -1
    mod_acces db "w",0
    text db "aw*gA?F6q!",0
    len equ $-text 
    aux resb 1
    

segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call[fopen]
        add ESP,4*2
        
        cmp EAX,0
        je final 
        
        mov [descriptor_fis],EAX
        
        mov ECX,len
        jecxz final 
        mov ESI,text 
        cld 
        
        bucla:
            push ECX 
            lodsb 
            mov [aux],AL 
            
            cmp byte[aux],'a'
            jb pass
            cmp byte[aux],'z'
            ja pass 
            add byte[aux],'A'-'a'
            
            pass:
                push dword aux
                push dword [descriptor_fis]
                call [fprintf]
                add ESP,4*2
                
            pop ECX
        loop bucla 
        
        push dword [descriptor_fis]
        call [fclose]
        add ESP,4
        
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
