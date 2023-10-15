alter view view1
as
	select distinct nume, COUNT(c.id_nota) FROM Studenti s 
	join Note n on
		s.id = n.id_student
	join Comentarii c on
		c.id_nota = n.id
where c.stare = 'deschis'
group by s.nume
