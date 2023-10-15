
GO
CREATE DATABASE Petreceri
GO 
USE Petreceri

CREATE TABLE Tipuri(
Tid INT PRIMARY KEY IDENTITY,
Nume VARCHAR(30),
Descriere VARCHAR(30)
);

CREATE TABLE Petreceri(
Pid INT PRIMARY KEY IDENTITY,
Nume VARCHAR(30),
Buget INT,
DataPetrecerii DATETIME,
Spatiu VARCHAR(30),
Tid INT FOREIGN KEY REFERENCES Tipuri(Tid)
);

GO
CREATE PROCEDURE AdaugaTip(
@Nume VARCHAR(30),
@Descriere VARCHAR(30))
AS
BEGIN
	INSERT INTO Tipuri(Nume,Descriere)
	VALUES (@Nume,@Descriere);	
END;
GO

EXEC AdaugaTip 'Halloween','31 octombrie'
EXEC AdaugaTip 'Ciubar','cu apa'

SELECT * FROM Tipuri



GO
CREATE PROCEDURE AdaugaPetrecere(
@Nume VARCHAR(30),
@Buget INT,
@DataPetrecerii DATETIME,
@Spatiu VARCHAR(30),
@Tip VARCHAR(30))
AS 
BEGIN
	DECLARE 
	@Tid INT = (SELECT TOP 1 Tid FROM Tipuri WHERE Nume = @Tip)

	IF @Tid IS NULL
		THROW 50001, 'Nu s-a gasit tipul petrecerii!',1;
	ELSE
		INSERT INTO Petreceri(Nume,Buget, DataPetrecerii, Spatiu, Tid)
		VALUES(@Nume,@Buget,@DataPetrecerii,@Spatiu,@Tid)

END;
GO

EXEC AdaugaPetrecere 'Halloween Party',50,'10/31/2021 19:00','Form Space','Halloween Party'
EXEC AdaugaPetrecere 'Paste Party',50,'10/31/2021 19:00','Form Space','Paste'
EXEC AdaugaPetrecere 'Ciubar',50,'11/22/2021 13:00','After Eight','Ciubar'
SELECT * FROM Petreceri


GO 
CREATE PROCEDURE CalculeazaBuget(
@Tip VARCHAR(30),
@Total INT OUTPUT
)
AS
BEGIN
	DECLARE 
	@Tid INT = (SELECT TOP 1 Tid FROM Tipuri WHERE Nume = @Tip)

	IF @Tid IS NULL
		SET @Total = 0;
	ELSE
		SET @Total = (SELECT SUM(Buget) FROM PETRECERI WHERE Tid=@Tid);

END;
GO

DECLARE @Total INT = 0;
EXEC CalculeazaBuget 'Ciubar', @Total=@Total OUTPUT;
PRINT @Total;