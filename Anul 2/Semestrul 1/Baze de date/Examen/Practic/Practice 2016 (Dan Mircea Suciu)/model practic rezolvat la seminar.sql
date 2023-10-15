
use master
GO
if exists(select * from master.sys.databases where name ='examen')
	drop database examen
create database examen
go
use examen

CREATE TABLE tipuri_tren
(
descriere varchar(256),
id int NOT NULL PRIMARY KEY

);

CREATE TABLE trenuri
(
	id int NOT NULL PRIMARY KEY,
	nume varchar(256),
	id_tip int
);

ALTER TABLE trenuri  WITH CHECK ADD  CONSTRAINT [FK_tren_tip] FOREIGN KEY(id_tip)
REFERENCES [tipuri_tren] ([id])

CREATE TABLE trasee
(
	id int NOT NULL PRIMARY KEY,
	nume varchar(256),
	id_tren int
);
ALTER TABLE trasee  WITH CHECK ADD  CONSTRAINT [FK_tren_traseu] FOREIGN KEY(id_tren)
REFERENCES [trenuri] ([id])

CREATE TABLE statii
(
	id int NOT NULL PRIMARY KEY,
	nume varchar(256),
);

CREATE TABLE orare
(
	traseu_id int ,
	statie_id int ,
	ora_plecare time NOT NULL ,
	ora_sosire time NOT NULL ,
	primary key (traseu_id, statie_id),
	
);
ALTER TABLE orare  WITH CHECK ADD  CONSTRAINT [FK_orar_statie1] FOREIGN KEY(statie_id)
REFERENCES [statii] ([id])
ALTER TABLE orare  WITH CHECK ADD  CONSTRAINT [FK_traseu_orar1] FOREIGN KEY(traseu_id)
REFERENCES [trasee] ([id])
GO
create procedure proc1 
@traseuId int,
@statieId int,
@oraSosire time,
@oraPlecare time
as
begin
	if exists(select * from orare where traseu_id =@traseuId and statie_id=@statieId )
		begin
			UPDATE orare
			SET ora_plecare=@oraPlecare,ora_sosire=@oraSosire
			WHERE traseu_id =@traseuId and statie_id=@statieId;
		end
	else
	begin
		INSERT INTO orare
		VALUES (@traseuId,@statieId,@oraPlecare,@oraSosire);

	end
	PRINT 'proc created'
end
GO


CREATE VIEW view1 AS
select trasee.nume
from (
	SELECT traseu_id
	FROM (select traseu_id, count(statie_id) as count1  from orare group by traseu_id) t1
	WHERE t1.count1=(select count(*) from statii)) t2,trasee
where t2.traseu_id=trasee.id

go


CREATE FUNCTION f1 (@tim time)
RETURNS @tab TABLE
   (
    statie_id int,
	count1 int,
	ora_plecare time
   )
AS
BEGIN
	insert into @tab
			select statie_id,count(id_tren) as count1,ora_plecare 

			from orare join trasee on orare.traseu_id=trasee.id

			where ora_plecare=@tim
			group by statie_id,ora_plecare
			having count(id_tren)>1
	return 
	
END;
GO

/*[use examen] select * from f1('1:1:1')  */