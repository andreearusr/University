bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fread,fclose,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        nume_fisier db "fisier.txt",0
        mod_acces db "r",0
        descriptor_fis dd -1
        text db 0
    
        contor_y dd 0
        contor_z dd 0
        format db "%d litere y si %d litere z",0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze nr-ul de litere
        ; 'y' si 'z' si sa se afiseze aceste valori. Numele fisierului este definit in segmentul de date
        
        ;fopen(nume_fisier,mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call[fopen]
        add ESP, 4*2
        
        cmp EAX,0
        je final
        
        mov [descriptor_fis],EAX
        
        bucla:
            ;fread(text,size,count,descriptor_fis)
            push dword [descriptor_fis]
            push dword 1
            push dword 1
            push dword text
            call [fread]
            add ESP, 4*4
            
            cmp EAX,0
            je cleanup

            mov CL, [text]
            cmp CL,'y'
            je calc_y
            
            cmp CL,'z'
            je calc_z
            
            jmp bucla
            calc_y:
                inc dword[contor_y]
            
            jmp bucla 
            calc_z:
                inc dword[contor_z]
           
        jmp bucla
        
    cleanup:
        ;printf(format,val1,val2)
        push dword [contor_z]
        push dword [contor_y]
        push dword format
        call[printf]
        add ESP,4*3
        
        ;fclose(descriptor_fis)
        push dword[descriptor_fis]
        call [fclose]
        add ESP, 4*1
        
    final:
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
