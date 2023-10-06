bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,scanf,printf,fread               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        n dd 0 
        mod_citire_n db "%x", 0 
        mod_afisare db "%c", 0 
        nume_fisier db "in.txt", 0 
        mod_citire db "r", 0 
        descriptor_fisier dd 0 
        string times 1 db 0  

; our code starts here
segment code use32 class=code
    start:
        ; ...Se citeste de la tastatura un numar n in baza 16 care poate fi reprezentat pe un cuvant (nu se fac validari in ;acest sens). Sa se deschida fisierul in.txt care contine exact 16 octeti si sa se afiseze pe ecran acei octeti din ;fisier care se afla pe pozitiile corespunzatoare bitilor 1 din reprezentarea binara a numarului n citit
    
        ;Exemplu: 
        ;n = F2A1h = 1111 0010 1010 0001b 
        ;in.txt = 0123456789abcdef 
        ;=> se va afisa pe ecran 0579cdef 
        
        push dword n
        push dword mod_citire_n 
        call [scanf] 
        add esp, 4 * 2 
        
        push dword mod_citire 
        push dword nume_fisier 
        call [fopen] 
        add esp, 4 * 2 
        
        cmp EAX, 0 
        jz final
        mov [descriptor_fisier], EAX
        
        Mov ECX, 16 

        bucla: 
            push dword [descriptor_fisier] 
            push dword 1 
            push dword 1 
            push dword string 
            call [fread] 
            add esp, 4 * 4 
            
            SHR dword[n], 1 
            jnc urmatorul 
            
            mov ebx, 0 
            mov bl, [string] 
            
            push dword ebx 
            push dword mod_afisare 
            call [printf] 
            add esp, 4 * 2 

            urmatorul: 
        loop bucla
        
        final: 
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
