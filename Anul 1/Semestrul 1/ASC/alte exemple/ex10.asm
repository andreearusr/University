bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 106
    mesaj_citire dd "Introduceti numarul b:",0
    mesaj_rezultat dd "Rezultatul lui %d + %d/%d este: %d",0
    mesaj_zero dd "Nu se poate face impartirea cu 0!",0
    b dd 0
    format_b dd "%d"

; our code starts here
segment code use32 class=code
    start:
        ; ...Se da un numar natural a (a: dword). Sa se citeasca un nr natural b si sa se calculeze a+a/b 
        ;  Sa se afiseze rezultatul operatiei. Valorile vor fi afisate in format decimal(baza 10) cu semn
        
        push dword mesaj_citire
        call[printf]
        add ESP, 4*1
        
        push dword b
        push format_b
        call[scanf]
        add ESP, 4*2
        
        cmp dword[b],0
        jz zero
        mov EAX,[a]
        cdq 
        idiv dword[b]
        add EAX, dword[a]
        
        push dword EAX
        push dword[b]
        push dword[a]
        push dword[a]
        push mesaj_rezultat
        call[printf]
        add ESP,4*5
        
        jmp sfarsit
        zero:
            push dword mesaj_zero
            call[printf]
            add ESP,4*1
        sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
