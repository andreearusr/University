USE [examen]
GO
/****** Object:  StoredProcedure [dbo].[proc1]    Script Date: 1/31/2016 11:52:19 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

create procedure [dbo].[proc1]
	@nume_angajat varchar(30),
	@numar_inmatriculare varchar(30),
	@motorizare varchar(30),
	@marca varchar(30),
	@nume_client varchar(30),
	@data_inchiriere datetime,
	@data_returnare datetime,
	@tip_operatie bit
as
BEGIN

	declare @id_angajat int
	select @id_angajat = a.id from Angajati a where a.nume = @nume_angajat

	declare @id_marca int
	select @id_marca = m.id from Marci m where m.denumire = @marca

	declare @id_autovehicule int
	select @id_autovehicule = au.id from Autovehicule au where au.numar_inmatriculare = @numar_inmatriculare and au.motorizare = @motorizare

	declare @id_client int
	select @id_client = c.id from Clienti c where c.nume = @nume_client

	
	if(@tip_operatie = 1)
	BEGIN
		insert into Evidenta(id_angajat, id_autovehicul, id_client, data_inchiriere, data_returnare)
		values(@id_angajat, @id_autovehicule, @id_client, @data_inchiriere, @data_returnare)
	END
	else
		BEGIN
			declare @id_evidenta int 
			select @id_evidenta = e.id from Evidenta e where e.id_client = @id_client and e.id_angajat = @id_angajat and e.id_autovehicul = @id_autovehicule
			Update Evidenta
			SET data_inchiriere = @data_inchiriere, data_returnare = @data_returnare
			where id = @id_evidenta

		END

END
