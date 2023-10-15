;suma nr pare -suma nr impare de la toate nivelurile unei liste
(defun s1(l)
  (cond
    ((and (atom l) (equal (mod l 2) 0)) l)
    ((atom l) 0)
    (t (apply #'+ (mapcar 's1 l)))
  )
)
(defun s2(l)
  (cond
    ((and (atom l) (not (equal 0 (mod l 2)))) l)
    ((atom l) 0)
    (t (apply #'+ (mapcar 's2 l)))
  )
)
(defun diferenta(l)
  (- (s1 l) (s2 l))
)

(print (diferenta '(1 2 3 4 6) ))