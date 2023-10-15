(defun dim(Arbore)
  (cond
   ((null (cdr Arbore)) 0)
   (T (+ 1 (APPLY #'MAX (MAPCAR #'dim (cdr Arbore)) )))
  )
)

(defun nivel (Arbore Nod)
	(cond
		((and (null (cdr Arbore)) (equal (car Arbore) Nod)) 0)
		(T ( + 1 (APPLY #'MAX (MAPCAR (lambda(aux) (nivel aux Nod )) (cdr Arbore)) )))
	)
)

(defun inaltime(Arbore Nod) 
  (cond 
   ((NULL (nivel Arbore Nod)) 0) 
   ( T (- (dim Arbore) (nivel Arbore Nod))) 
  )
)

(print (dim '(a (b (g)) (c (d (e)) (f))) ))

(print (nivel '(a (b (g)) (c (d (e)) (f))) 'c))