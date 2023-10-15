use examen
go

create view view1
as
select DISTINCT nume, COUNT(*) as Numar_inchirieri from Angajati a
join Marci m on m.denumire = 'Audi'
join Evidenta e on e.id_angajat = a.id and month(data_inchiriere) = 1
group by nume