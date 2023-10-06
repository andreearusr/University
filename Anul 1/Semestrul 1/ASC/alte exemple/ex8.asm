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
        mesaj_a db "a=",0
        mesaj_b db "b=",0
        format_1 db "%d",0
        format_2 db "Suma numerelor a si b este:%x",0
        a resd 1
        b resd 1 
        suma resd 1


; our code starts here
segment code use32 class=code
    start:
        ; ...Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze a+b
        ;    Sa se afiseze rezultatul adunarii in baza 16
        
        push dword mesaj_a
        call[printf]
        add ESP, 4*1
        
        push dword a
        push dword format_1
        call[scanf]
        add ESP, 4*2
        
        push dword mesaj_b
        call[printf]
        add ESP, 4*1
        
        push dword b 
        push dword format_1
        call[scanf]
        add ESP, 4*2
        
        mov EAX,dword[a]
        add EAX,dword[b]
        
        push EAX
        push format_2
        call[printf]
        add ESP, 4*2
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
