
;suma nr pare - suma nr impare la toate nivelurile unei liste

(defun s1(x)
  (cond
	((and (numberp x) (equal (mod x 2) 0)) x)
    ((atom x) 0)
    (t (apply '+ (mapcar #'s1 x)))
  )
)

(defun s2(x)
  (cond
	((and (numberp x) (equal (mod x 2) 1)) x)
    ((atom x) 0)
    (t (apply '+ (mapcar #'s2 x)))
  )
)
(defun diferenta(l)
  (- (s1 l) (s2 l))
)

(print (diferenta '(1 2 d 4 6) )) ; 2+4+6 - 1 = 11
(print (diferenta '(1 2 (d 2 2) (3 5) 4 6) )) ; 2+2+2+4+6 - (1+3+5) = 16 - 9 = 7