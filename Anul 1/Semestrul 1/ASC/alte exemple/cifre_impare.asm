bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fread,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        fisier db "fisier2.txt"
        mod_acces db "r",0
        descriptor dd -1
        max equ 1
        text db 0
        
        contor dd 0
        format db "%d cifre impare",0

; our code starts here
segment code use32 class=code
    start:
        ; Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de cifre impare si
        ; sa se afiseze aceasta valoare. Functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        
        push dword mod_acces
        push dword fisier
        call[fopen]
        add ESP, 4*2
        
        mov [descriptor],EAX
        cmp EAX,0
        je final
        
        bucla:
            push dword [descriptor]
            push dword max
            push dword 1  ; 1 octet pt ca sunt caractere
            push dword text
            call [fread]
            add ESP, 4*4
            
            cmp EAX,0
            je final
            
            mov AL,[text]
            cmp AL,'0'
            jl bucla
            
            cmp AL,'9'
            jg bucla
            
            mov AH,0   ;AH- caracterul citit
            mov BH,2
            div BH
            
            cmp AH,0
            je bucla
            
            inc dword[contor]
            
        jmp bucla
        
        final:
        push dword [contor]
        push format
        call [printf]
        add ESP, 4*2
        
        push dword [descriptor]
        call [fclose]
        add ESP, 4*1
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
