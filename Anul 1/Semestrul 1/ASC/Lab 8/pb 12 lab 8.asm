bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ... se da un sir A de dublucuvinte. Construiti 2 siruri de octeti:
    ;               B1 contine ca elem. partea inferioara a cuvintelor inferioare din A
    ;               B2 contine ca elem. partea superioara a cuvintelor superioare din A
    
    A dd 12345678h,53247816h,93721452h,84563217h
    lA equ ($-A)/4      ; lungimea sirului in dublucuvinte
    B1 times lA db 0    ; 78h,16h,52h,17h
    B2 times lA db 0    ; 12h,53h,93h,84h

; our code starts here
segment code use32 class=code
    start:
        mov ECX,lA
        mov ESI,A          ; incarcare offset sirului sursa A in ESI
        mov EDI,B1         ; incarcare offset sir destinatie B1 in EDI      
        cld                ; parcurgem sirul de la stanga la dreapta
        jecxz Urmatorul
        
        formeaza_B1:
            LODSB          ;AL <-- octetul de la DS:ESI, inc ESI
            STOSB          ;ES:EDI <-- octetul din AL, inc EDI
            LODSW
            LODSB
        loop formeaza_B1
 
        Urmatorul:
        mov ECX,lA
        mov ESI,A
        mov EDI,B2
        cld 
        jecxz Final
        
        formeaza_B2:
            LODSW
            LODSB
            LODSB           ;AL <-- octetul superior de la DS:ESI, inc ESI
            STOSB           ;ES:EDI <-- octetul din AL, inc EDI   
        loop formeaza_B2
        
        Final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
