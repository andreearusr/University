
bits 32
global start

extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll


segment data use32 class=data 
    sir_cuv dw 21520,-6,'xy',0F5B2h,-129
    
    len equ ($-sir_cuv)/2
    sir1 times len db 0
    sir2 times len db 0
    
    mesaj1 db "Cat= ",0
    mesaj2 db "Rest= ",0
    
    format db "%x ",0
    
segment code use32 class=code 
start:
    
    mov ECX,len
    mov ESI,sir_cuv
    mov EDI,sir1
    jecxz final
    cld 
    
    bucla:
        lodsb 
        stosb
        lodsb
    loop bucla 
    
    final:
    mov DL,1
    repeta:
        cmp DL,0
        jz final2
        mov DL,0
        mov ECX,len-1
        mov ESI,sir1
        repeta2:
            mov AL,[ESI]
            mov BL,[ESI+1]
            cmp AL,BL
            jge next
            
            mov [ESI],BL
            mov [ESI+1],AL
            mov DL,1
            next:
                inc ESI
        loop repeta2
    jmp repeta
    
    
    final2:
    mov ECX,len
    mov ESI,sir_cuv
    mov EDI,sir2
    jecxz final3
    cld
    
    bucla2:
        lodsb
        lodsb
        stosb
    loop bucla2
    
    final3:
    mov DL,1
    repeta3:
        cmp DL,0
        jz final4
        mov DL,0
        mov ECX,len-1
        mov ESI,sir2
        repeta4:
            mov AL,[ESI]
            mov BL,[ESI+1]
            cmp AL,BL
            jle next1
            
            mov [ESI],BL
            mov [ESI+1],AL
            mov DL,1
            next1:
                inc ESI
        loop repeta4
    jmp repeta3
    
    final4:
    mov ESI,sir1
    cld
    lodsb ;AL<-maximul valorilor octetilor inferiori 
    mov AH,0  ;AX<-maximul
    
    mov BX,AX   ;BX<-maximul
    
    mov ESI,sir2 
    cld 
    lodsb ;AL<-minimul valorilor octetilor inferiori 
   
    mov DL,AL ;DL<-minimul=b 
    
    mov AX,BX   ;AX <-maxim=a
    div DL   ;AL cat   AH rest
    
    mov DL,AH 
    
    mov AH,0  ;AX cat 
    mov BX,AX
    mov EAX,0
    mov AX,BX 
    
    pushad
    push dword mesaj1 
    call [printf]
    add esp,4*1
    popad 
    
    push edx 
    push dword EAX
    push dword format
    call [printf]
    add esp,4*2
    pop edx 
    
    mov AL,DL
    mov AH,0   
    mov BX,AX
    mov EAX,0
    mov AX,BX ;EAX restul
    
    pushad
    push dword mesaj2 
    call [printf]
    add esp,4*1
    popad 
    
 
    push dword EAX
    push dword format
    call [printf]
    add esp,4*2

    push dword 0
    call [exit]