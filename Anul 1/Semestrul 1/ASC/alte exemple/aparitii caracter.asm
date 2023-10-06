bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        
        car dd 0
        s db "Andrei are mere",0
        mesaj1 db "Caracter introdus: ",0
        mesaj2 db "Numarul de aparitii: ",0
        space db " ",0
        format db "%c",0
        format2 db "%d",0

; our code starts here
segment code use32 class=code
    start:
        ; Se da un sir de caractere(def in segm de date). Sa se citeasca de la tastatura un caracter, sa se det nr de aparitii
        ; al acelui caract in sirul dat si sa se afiseze acel caracter impreuna cu nr de aparitii
    
        mov EBX,0
        
        push dword car
        push dword format
        call[scanf]
        add ESP,4*2
        
        mov ESI,s
        mov EAX,[car]
        mov AH,AL    ;punem in ah caracterul
        cld          ; parcurgem sirul de la stanga la dreapta
        nr_aparitii:
            lodsb    ; punem in al caracter cu caracter
            cmp AL,0
            jz done
            
            cmp AL,AH
            jne nu_cresc_nr_aparitii
            inc EBX   ; creste nr de aparitii
            
        nu_cresc_nr_aparitii:
            cmp AL,0
            jnz nr_aparitii   ; daca nu s-a ajuns inca la 0 se repeta
            
        done:
            push dword mesaj1
            call[printf]
            add ESP,4*1
            
            push dword car 
            call [printf]   ; afisam mesajul "Caracter introdus: " si caracterul introdus
            add ESP,4*1
            
            push dword space
            call [printf]
            add ESP, 4*1
            
            push dword mesaj2
            call[printf]
            add ESP,4*1
            
            push dword EBX
            push dword format2
            call[printf]   ; afisam mesajul "Numarul de aparitii: " si numarul de aparitii
            add ESP, 4*2
            
            
            
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
