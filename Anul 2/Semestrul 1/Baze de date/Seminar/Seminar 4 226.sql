CREATE DATABASE Seminar4_226;
GO
USE Seminar4_226;
CREATE TABLE Produse
(cod_p INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
pret FLOAT,
tip VARCHAR(100),
cantitate INT,
producator VARCHAR(100),
data_expirarii DATE
);

INSERT INTO Produse (nume, pret, tip, cantitate, producator, data_expirarii) 
VALUES ('ciocolata',10,'dulciuri',20,'Milka','2023-01-01'),
('lapte',11,'lactate',10,'Zuzu','2021-12-18'),
('salam',18,'mezeluri',15,'Fox','2022-05-03'),
('penar',50,'rechizite',50,'Herlitz',NULL),
('pix',2,'rechizite',100,'Bic',NULL),
('branza',15,'lactate',7,'Hochland','2023-07-02'),
('rigla',3,'rechizite',75,'Bic',NULL),
('banane',5,'fructe',40,'Chiquita','2021-11-22');

SELECT * FROM Produse;
GO
--functie scalara
CREATE FUNCTION ufNrProduseFaraDataExpirare()
RETURNS INT 
AS
BEGIN
DECLARE @nrproduse INT=0;
SELECT @nrproduse=COUNT(*) FROM Produse WHERE data_expirarii IS NULL;
RETURN @nrproduse;
END;
GO
--apelul functiei
PRINT dbo.ufNrProduseFaraDataExpirare();
GO
--functie inline table valued
CREATE FUNCTION ufNumePretRechizite()
RETURNS TABLE AS
RETURN SELECT nume, pret FROM Produse WHERE tip='rechizite';
GO
--apelul functiei
SELECT * FROM dbo.ufNumePretRechizite();
GO
--functie multi statement table valued
CREATE FUNCTION ufProduseInterval (@pret_min FLOAT, @pret_max FLOAT)
RETURNS @ProduseInterval TABLE (nume VARCHAR(100), pret FLOAT) 
AS
BEGIN
IF(@pret_min <= 0 OR @pret_min>@pret_max OR @pret_min=@pret_max)
	INSERT INTO @ProduseInterval (nume, pret) VALUES ('intervalul introdus este
	invalid!',0);
ELSE
	INSERT INTO @ProduseInterval (nume, pret) SELECT nume, pret FROM Produse
	WHERE pret BETWEEN @pret_min AND @pret_max;
RETURN;
END;
GO
--apelul functiei
SELECT * FROM dbo.ufProduseInterval(1,10);
SELECT * FROM dbo.ufProduseInterval(1,1);
SELECT * FROM dbo.ufProduseInterval(0,1);
SELECT * FROM dbo.ufProduseInterval(12,1);
--definitia unei functii cu sp_helptext
EXEC sp_helptext 'dbo.ufProduseInterval';
--definitia unei functii cu OBJECT_DEFINITION
PRINT OBJECT_DEFINITION(OBJECT_ID('dbo.ufProduseInterval'));
GO
--view
CREATE VIEW vw_Produse
AS
SELECT nume, pret , producator FROM Produse;
GO
--interogarea view-ului
SELECT * FROM vw_Produse;
SELECT * FROM vw_Produse ORDER BY nume ASC;
--definitia unui view cu sp_helptext
EXEC sp_helptext 'dbo.vw_Produse';
--definitia unui view cu OBJECT_DEFINITION
PRINT OBJECT_DEFINITION(OBJECT_ID('dbo.vw_Produse'));
GO
--trigger pentru insert
CREATE TRIGGER La_inserare_produs
ON Produse
FOR INSERT
AS
BEGIN
SELECT nume, pret, pret*cantitate AS [pret total] FROM inserted;
END;
GO
--declansarea trigger-ului
INSERT INTO Produse (nume, pret, cantitate, tip, producator, data_expirarii) VALUES
('produs de test',2,10, 'tip de test', 'producator de test', NULL);
GO
--trigger pentru delete
CREATE TRIGGER La_stergere_produs
ON Produse
FOR DELETE
AS
BEGIN
SELECT nume, pret, cantitate, pret*cantitate AS [pret total] FROM deleted;
END;
GO
--declansarea trigger-ului
DELETE FROM Produse WHERE nume = 'produs de test';
--definitia trigger-ului cu sp_helptext
EXEC sp_helptext 'dbo.La_stergere_produs';
--definitia trigger-ului cu OBJECT_DEFINITION
PRINT OBJECT_DEFINITION(OBJECT_ID('dbo.La_stergere_produs'));

