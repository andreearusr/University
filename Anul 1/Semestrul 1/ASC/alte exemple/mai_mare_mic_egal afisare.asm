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
        a dd 0
        b dd 0
        format db "%d",0
        paranteze db "<%d>",0
        egal db "=",0
        mai_mic db "<",0
        mai_mare db ">",0

; our code starts here
segment code use32 class=code
    start:
        ; Sa se citeasca de la tastatura 2 numere a si b (in baza 10) si sa se det relatia de ordine dintre ele
        ; (a<b, a=b sau a<b). Afisati rez il urmat format: "<a> < <b>, <a>=<b> sau <a> > <b>"
        
        push dword a
        push dword format
        call [scanf]
        add ESP, 4*2
        
        push dword b
        push dword format
        call [scanf]
        add ESP, 4*2
        
        push dword [a]
        push dword paranteze
        call [printf]
        add ESP, 4*2
        
        mov EAX,[a]
        mov EBX,[b]
        cmp EAX,EBX
        
        jl print_mai_mic
        je print_egal
        jg print_mai_mare
        
        print_mai_mic:
            push dword mai_mic 
            call [printf]
            jmp final
        print_egal:
            push dword egal
            call[printf]
            jmp final
        print_mai_mare:
            push dword mai_mare
            call [printf]
            jmp final
        
        final:
            add ESP,4*1
            
        push dword [b]
        push dword paranteze
        call [printf]
        add ESP, 4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
