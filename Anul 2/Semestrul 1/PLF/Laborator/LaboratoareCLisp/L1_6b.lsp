(defun pereche (l1 l2)
	(cond
		((or (null l1) (null l2)) nil)
		(t  (cons (cons (car l1) (car l2)) (pereche (cdr l1) (cdr l2)) ))
	)
)

(print (pereche '(a b c) '(x y z)))
(print (pereche '(1 2 3) '(5 6 7)))
(print (pereche '(1 2 3) '(5)))
(print (pereche '() '()))
