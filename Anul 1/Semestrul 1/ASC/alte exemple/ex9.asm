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
    rezultat dd 0
    mesaj_a db "a=",0
    mesaj_b db "b=",0
    mesaj_rezultat db "(a+b)/(a-b) = %d",0
    mesaj_divide_by_zero db "Nu se poate imparti la zero!",0
    format_citire db "%d",0

; our code starts here
segment code use32 class=code
    start:
        ; ...Sa se citeasca de la tastatura 2 nr a si b (in baza 10) si sa se calculeze (a+b)/(a-b)
        ; Catul imp se va salva in memorie in variabila rezultat
        ; Valorile se considera cu semn
        
        push dword mesaj_a
        call[printf]
        add ESP,4*1
        
        push dword a
        push dword format_citire
        call[scanf]
        add ESP,4*2
        
        push dword mesaj_b
        call[printf]
        add ESP,4*1
        
        push dword b
        push dword format_citire
        call[scanf]
        add ESP, 4*2
        
        mov EAX,[a]
        add EAX,[b]
        cdq
        mov EBX,[a]
        sub EBX,[b]
        cmp EBX,0
        je divide_by_zero
        idiv EBX
        mov [rezultat],EAX 
        
        
        push dword[rezultat]
        push dword mesaj_rezultat
        call[printf]
        add ESP, 4*2
        
        jmp final
        
        divide_by_zero:
            push dword mesaj_divide_by_zero
            call[printf]
            add ESP, 4*1
        final:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
