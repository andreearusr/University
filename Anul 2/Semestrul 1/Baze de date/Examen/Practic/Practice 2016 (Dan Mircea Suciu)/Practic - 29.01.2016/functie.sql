select nume, final = (select SUM(nota)/COUNT(*) from Note where Note.id_student = Studenti.id)
from Studenti where id_grupa = 1