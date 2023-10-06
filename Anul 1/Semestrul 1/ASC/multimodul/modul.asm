bits 32

global modul
segment code use 32 class=code public

modul:
    ;[ESP+4] <- valoarea variabilei n
    ;[ESP+8] <- valoarea variabilei x
    
    mov EAX,[ESP+4]
    cmp EAX,[ESP+8]
    jbe iesire
    
    mov EAX,[ESP+8]
    
    iesire:
        ret 
       
    