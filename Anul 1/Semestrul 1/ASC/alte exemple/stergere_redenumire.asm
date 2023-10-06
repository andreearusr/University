bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fprintf,rename,remove,fread               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import remove msvcrt.dll
import rename msvcrt.dll
import fread msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        nume_fisier db "a.txt", 0 
        nume_fisier_scriere db "b.txt", 0 
        mod_citire db "r", 0 
        mod_adaugare db "a", 0 
        descriptor_fisier resd 1 
        descriptor_fisier_scriere resd 1 
        format_afisare db "%c", 0 
        text   times 1 db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...Se citeste continutul unui fisier (a.txt) si se adauga 1 la fiecare octet citit. Apoi, se scriu octetii rezultati ;in fisierul b.txt. Se redenumeste la finalul scrierii fisierul b.txt in a.txt si se sterge fisierul b.txt din ;folderul curent 
    
        push dword mod_citire 
        push dword nume_fisier 
        call [fopen] 
        add esp, 4 * 2 
        
        cmp eax, 0 
        jz sfarsit 
        mov [descriptor_fisier], eax 
        
        push dword mod_adaugare 
        push dword nume_fisier_scriere 
        call [fopen] 
        add esp, 4 * 2 
        
        mov [descriptor_fisier_scriere], eax
        cmp eax, 0 
        jz sfarsit 
        
        bucla: 
            push dword [descriptor_fisier] 
            push dword 1 
            push dword 1 
            push dword text 
            call [fread] 
            add esp, 4 * 4 
            
            cmp eax, 0 
            je cleanup
            
            add byte [text], 1 
            mov ebx, 0 
            mov bl, byte[text] 
            
            push ebx 
            push dword format_afisare 
            push dword [descriptor_fisier_scriere] 
            call [fprintf] 
            add esp, 4 * 3 

        jmp bucla 
        
        cleanup: 
            push dword [descriptor_fisier] 
            call [fclose] 
            add esp, 4 * 1 
            
            push dword [descriptor_fisier_scriere] 
            call [fclose] 
            add esp, 4 * 1 
        
        ;remove(path) 
        push dword [nume_fisier] 
        call [remove] 
        add esp, 4 * 1 
 
        ;rename(oldname, newname) 
        push dword [nume_fisier] 
        push dword [nume_fisier_scriere] 
        call [rename] 
        add esp, 4 * 2 
        
        sfarsit:

 
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
