bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        sir dd 00005678h, 1256ABCDh, 12344344h
        len equ ($-sir)/4; lungimea sirului in dublucuvinte
        s times len dw 0

; our code starts here
segment code use32 class=code
    start:
        ; ...Se da un sir de dublucuvinte. Sa se ordoneze crescator sirul cuvintelor superioare ale acestor dublucuvinte.
        ; Cuvintele inferioare raman neschimbate
    
        mov ESI,sir
        cld 
        mov ECX,len
        jecxz sfarsit
        mov EDI,0
        repeta:
            lodsw; AX <- cuv mai putin semnificativ 
            lodsw; AX <- cuv cel mai semnificativ 
            mov [s+EDI],AX; punrm cuv superioare in sirul s
            add EDI,2
        loop repeta
        
        sfarsit:
        
        mov ECX,len
        mov ESI,0
        jecxz sfarsit1
        repeta1:
            mov AX,[s+ESI]
            mov EDX,ECX
            dec ECX 
            jecxz sfarsit2
            mov EDI,ESI
            add EDI,2
            repeta2:
                mov BX,[s+EDI]
                cmp AX,BX; comparam 2 elem din sirul s
                jb sari
                mov [s+EDI],AX
                mov [s+ESI],BX
                mov AX,BX 
                sari:
                    add EDI,2
            loop repeta2
            sfarsit2:
                add ESI,2
            mov ECX,EDX 
        loop repeta1
        sfarsit1:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
