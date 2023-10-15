(defun dublare_el_poz (l poz n)
	(cond
		((null l) nil)
		((= poz n) (cons (car l) (cons (car l) (dublare_el_poz (cdr l) (+ poz 1) n))))
		(t (cons (car l) (dublare_el_poz (cdr l) (+ poz 1) n)))
	)
)

(defun dublareAux (l n)
	(dublare_el_poz l 1 n)
)

(print (dublareAux '(1 2 3) 1))
(print (dublareAux '(10 20 30 40 50) 3))
(print (dublareAux '() 5))
(print (dublareAux '(1 2 3 4 5) 8))