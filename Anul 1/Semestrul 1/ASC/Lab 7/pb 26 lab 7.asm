bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    S db 3,8,2,10,7,1,9
    l equ $-S
    max_pare db 0
    min_impare db 0

; our code starts here
segment code use32 class=code
    start:
        ; ... se da un sir de octeti S. Sa se detetrmine:
        ;                                     maximul elem de pe pozitiile pare
        ;                                     minimul elem de pe pozitiile impare
        
        mov ESI,0
        mov AL,0   ; in AL calculam maximul de pe pozitiile pare
        mov BL,0   
        mov ECX, l
        
        jecxz Urmatorul 
        transforma_pare:
            mov BL,[S+ESI]   ; pozitia curenta in sir
            cmp AL,BL
                ja continua1
                mov AL,BL
            continua1:
                add ESI,2
        cmp ESI,ECX
        jb transforma_pare
        
        mov [max_pare], AL
        
        
        Urmatorul:
        mov ESI,1
        mov AL,0   ; in Al calculam minimul de pe pozitiile impare
        mov BL,0
        mov ECX,l
        
        jecxz final
        transforma_impare:
            mov BL,[S+ESI]   ; pozitia curenta in sir
            cmp AL,BL
                jb continua2
                mov AL,BL
            continua2:
                add ESI,2
        cmp ESI,ECX
        jb transforma_impare
        
        mov [min_impare], AL 
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
