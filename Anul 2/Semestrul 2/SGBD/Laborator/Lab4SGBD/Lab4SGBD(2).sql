GO
USE ClinicaStomatologica
GO


--dirty reads --un cititor citeste date necomise(2)
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRAN
SELECT * FROM Serviciu;
COMMIT TRAN

SELECT * FROM Serviciu



--non-repetable reads --o inr existenta se schimba in cadrul unei tranzactii(2)
BEGIN TRAN
WAITFOR DELAY '00:00:03'
UPDATE Serviciu SET Durata=30
WHERE Denumire='Obturatie provizorie'
COMMIT TRAN



--phantom reads --sunt adaugate noi inr si apar in cadrul unei tranzactii(2)
BEGIN TRAN
WAITFOR DELAY '00:00:03'
INSERT INTO Serviciu(CodS,Denumire,Pret,Durata)
VALUES (14,'Gutiera',280,30)
COMMIT TRAN


--deadlock(2)
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
BEGIN TRAN
UPDATE Serviciu SET Denumire='Activare aparat' where Denumire='Activare aparat fix'
WAITFOR DELAY '00:00:10'
UPDATE Medicament SET Pret=35 WHERE Denumire='Nurofen'
COMMIT TRAN




GO
CREATE OR ALTER PROCEDURE deadlock1
AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
	BEGIN TRAN
	UPDATE Serviciu SET Denumire='Activare aparat' where CodS=55
	WAITFOR DELAY '00:00:05'
	UPDATE Medicament SET Pret=35 WHERE Denumire='Nurofen'
	COMMIT TRAN
END;

GO
CREATE OR ALTER PROCEDURE deadlock2
AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
	BEGIN TRAN
	UPDATE Medicament SET Pret=32 WHERE Denumire='Nurofen'
	WAITFOR DELAY '00:00:05'
	UPDATE Serviciu SET Denumire='Activare' where CodS=55
	COMMIT TRAN
END;

select * from Serviciu
select * from Medicament

UPDATE Serviciu SET Denumire='Activare aparat fix' where CodS=55
UPDATE Medicament SET Pret=32 WHERE Denumire='Nurofen'
