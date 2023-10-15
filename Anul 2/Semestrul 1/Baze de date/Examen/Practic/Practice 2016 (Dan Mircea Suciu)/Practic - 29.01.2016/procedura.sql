USE [examen2]
GO
/****** Object:  StoredProcedure [dbo].[proc1]    Script Date: 1/29/2016 16:13:09 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER procedure [dbo].[proc1]
	@nume_student varchar(30),
	@nume_task varchar(30),
	@nota int,
	@comentariu varchar(30)
as
BEGIN
	
	declare @id_student int
	select @id_student = s.id from Studenti s where s.nume = @nume_student

	declare @id_task int
	select @id_task = t.id from Taskuri t where t.nume = @nume_task

	declare @id_nota int

	if ( not exists (Select n.nota from Note n where n.id_student = @id_student and n.id_task = @id_task ))
		BEGIN
			insert into Note(nota, id_task, id_student)
			values(@nota, @id_task, @id_student)

			
			select @id_nota = n.id from Note n where n.nota = @nota and n.id_student = @id_student and n.id_task = @id_task

			INSERT INTO Comentarii (id_nota, stare) VALUES (@id_nota, @comentariu)
		END
	else
		BEGIN
			
			select @id_nota = n.id from Note n where n.nota = @nota and n.id_student = @id_student and n.id_task = @id_task

			UPDATE Note
			SET nota = @nota WHERE id_task = @id_task and id_student = @id_student 

			INSERT INTO Comentarii (id_nota, stare) VALUES (@id_nota, @comentariu)
		END

	
END
