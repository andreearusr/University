bits 32

global start
extern exit,scanf,printf 
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data 
    numar dd 0
    format db "%u",0
    format1 db "%u",0
segment code use32 class=code
start:
    
    push dword numar
    push dword format
    call [scanf]
    add ESP,4*2
    
    mov EBX,dword[numar]
    
    mov AX,BX
    mov DX,0
    mov CX,2
    div CX  ; AX cat   DX rest
    
    mov SI,AX 
    mov DX,1   ; pp ca e prim
    
    mov CX,2
    
    bucla:
        cmp CX,SI
        ja stop
        
        mov AX,BX 
        mov DX,0
        div CX 
        
        cmp DX,0
        je final 
        
        add CX,1
        
    jmp bucla
    
    
    stop:
    push dword [numar]
    push dword format1
    call [printf]
    add ESP,4*2
    
    
    final:
    push dword 0
    call [exit]
    