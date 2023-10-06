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
    n dd 0
    mesaj db "n = ",0
    format db "%x",0
    mesaj2 db "Numarul in baza 10 fara semn este:",0
    format2 db "%u",0
    mesaj3 db "  Numarul in baza 10 cu semn este:",0
    format3 db "%d",0

; our code starts here
segment code use32 class=code
    start:
        push dword mesaj
        call [printf]
        add ESP, 4*1
        
        push dword n 
        push dword format
        call [scanf]
        add ESP, 4*2
        
        push dword mesaj2
        call[printf]
        add ESP, 4*1
        
        mov EAX,[n]
        
        mov BL,AL
        mov EAX,0
        mov AL,BL
        
        pushad
        
        push dword EAX 
        push dword format2
        call[printf]
        add ESP,4*2
        
        popad
        
        cbw
        cwde
        
        pushad
        push dword mesaj3
        call[printf]
        add ESP, 4*1
        popad
        
        push dword EAX
        push dword format3
        call [printf]
        add ESP, 4*2
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
