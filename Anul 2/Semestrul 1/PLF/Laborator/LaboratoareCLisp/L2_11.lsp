
;nr. atomi de la nivel superficial
(defun nrAtomi (l)
	(cond
		((null l) 0)
		((listp (car l)) (nrAtomi(cdr l))) 
		(t (+ 1 (nrAtomi(cdr l))) )
	)
)

;subarborii urmatori 
(defun subarb (l)
  (cond
	((null l) nil)
	((not (atom (car l))) (append (car l) (subarb(cdr l)) ) )
	( t ( subarb(cdr l)) )
  )
)

;nr maxim de noduri de pe nivelul cu numar maxim de noduri
(defun nrMax(l)
   (cond
	((null l) 0)
	((< (nrAtomi l) (nrMax (subarb l))) (nrMax(subarb l)) )
	(t (nrAtomi l))
   )
)

;lista nodurilor de pe nivelul cu nr maxim de noduri
(defun lNoduri (l)
   (cond
	((= (nrAtomi l) (nrMax l)) (atomii l) )
	(t (lNoduri (subarb l)))
   )
)

;atomii unei liste
(defun atomii (l)
   (cond 	
	((null l) nil)
	((atom (car l)) (cons (car l) (atomii(cdr l)) ))
	(t (atomii (cdr l)))
   )
)

;nivelul cu numar maxim de noduri
(defun nivel (l)
   (cond 
	((= (nrAtomi l) (nrMax l)) 0)
	(t (+ 1 (nivel (subarb l))))
   )
)

(defun rez (l)
	(print (nivel l))
	(print (lNoduri l))
)

(rez '(1))
(rez '(1 (2 (4) (5)) (3 (6) (7))))
(rez '(1 (2 (4 (8)) (5 (9) (10))) (3 (6 (11)) (7 (12)))))
(rez '(A (B () (D (F) (G))) (C () (E (H)))))
(rez '(A (B (D)) (C)))

;	    1
;   2       3
; 4  5     6  7
;8  9 10  11 12
 