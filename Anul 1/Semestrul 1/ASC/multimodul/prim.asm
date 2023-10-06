bits 32

global prim

segment data use32 class=data public
    divizor dw 3
    x1 dd 0
    
segment code use 32 class=code public 
    
    prim:
        mov EAX,[ESP+4]
        mov dword[x1],EAX 
        
        cmp dword [x1],1
        je .nu_este_prim
        
        cmp dword[x1],4
        jb .este_prim
        
        mov AX,[x1]
        and AX,0000000000000001
        cmp AX,0
        je .nu_este_prim
        
        .incearca_divizor:
            mov EBX,0
            mov BX, word[divizor]
            cmp EBX,dword[x1]
            je .este_prim
            
            mov EAX,dword[x1]
            
            push EAX
            pop AX
            pop DX
            
            div dword[divizor]
            cmp DX,0
            je .nu_este_prim
            inc word[divizor]
            jmp .incearca_divizor
        
        .este_prim:
            mov dword[ESP+4],1
            jmp .sfarsit_prim 
            
        .nu_este_prim:
            mov dword[ESP+4],0
        
        .sfarsit_prim:
            ret