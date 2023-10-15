(defun nrListe (l)
	(cond
		((null l) 1)
		((listp (car l))(+ (nrListe(car l)) (nrListe(cdr l))))
		(t (nrListe(cdr l)))
	)
)

(print (nrListe '(1 2 (3 (4 5) (6 7)) 8 (9 10))))
(print (nrListe '()))
(print (nrListe '(1 2)))
(print (nrListe '((1 2))))
(print (nrListe '(1 2 () 4 ())))