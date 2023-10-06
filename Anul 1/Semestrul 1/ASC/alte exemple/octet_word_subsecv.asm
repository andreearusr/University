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
        a resb 1
        b resw 1
        mesaja db "a=",0
        mesajb db "b=",0
        format1 db "%x",0
        format2 db "Da",0
        format3 db "Nu",0

; our code starts here
segment code use32 class=code
    start:
        ; Sa se citeasca de la tastatura un octet si un cuvant. Sa se afiseze pe ecran daca bitii octetului citit se 
        ; regasesc in bitii cuvantului 
        ; a = 10 = 0000 1010b
        ; b = 256 = 0000 0001 0000 0000b    Pe ecran se va afisa NU
        ; a = 0Ah = 0000 1010b
        ; b = 6151h = 0110 0001 0101 0001b   Se va afisa: DA (se regasesc pe pozitiile 5-12)
        
        push dword mesaja
        call[printf]
        add ESP,4*1
        
        push dword a 
        push dword format1
        call[scanf]    ;citeste a de tip hexa
        add ESP,4*2
        
        push dword mesajb
        call[printf]
        add ESP,4*1
        
        push dword b 
        push dword format1
        call[scanf]    ;citeste b de tip hexa
        add ESP,4*2
        
        mov ECX,8  ; deoarece sunt 8 posibili octeti in interiorul unui cuvant
        mov DL,0
        mov ESI,a 
        lodsb  ;AL=a
        mov BL,AL   ; in BL pastrez a pt a-l compara
        cld 
        jecxz sfarsit
        repeta:
            mov ESI,b 
            lodsb 
            lodsb   ;vom compara mereu octetul superior
            cmp BL,AL
            jnz sari
            mov DL,1
            sari:
                RCL word[b],1   ;pt a roti cuvantul
        loop repeta
        
        sfarsit:
        cmp DL,0
        jnz mesaj_da
        
        push dword format3
        call [printf]
        add ESP, 4*1
        
        cmp DL,0
        jz ending
        
        mesaj_da:
            push dword format2
            call[printf]
            add ESP, 4*1
            
        ending:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
