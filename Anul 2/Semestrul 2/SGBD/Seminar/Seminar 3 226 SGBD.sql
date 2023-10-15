CREATE DATABASE Seminar3226SGBD;
GO
USE Seminar3226SGBD;
CREATE TABLE Cafele
(cod_c INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
nr_shoturi INT,
nivel_dulce INT
);
INSERT INTO Cafele (nume, nr_shoturi, nivel_dulce) VALUES
('americano',1,0),('flat white',2,30),('cappuccino',1,55);
--tranzactie autocommit
SELECT * FROM Cafele;
--tranzactii implicite
SET IMPLICIT_TRANSACTIONS ON;
SELECT @@TRANCOUNT;
SELECT * FROM Cafele;
SELECT @@TRANCOUNT;
INSERT INTO Cafele(nume, nr_shoturi, nivel_dulce) VALUES
('espresso temporar',1,-10);
SELECT * FROM Cafele;
SELECT @@TRANCOUNT;
ROLLBACK TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Cafele;
SELECT @@TRANCOUNT;
INSERT INTO Cafele(nume, nr_shoturi,nivel_dulce) VALUES
('espresso permanent',1,-20);
SELECT @@TRANCOUNT;
SELECT * FROM Cafele;
COMMIT TRAN;
SELECT @@TRANCOUNT;
SET IMPLICIT_TRANSACTIONS OFF;
SELECT * FROM Cafele;
SELECT @@TRANCOUNT;
--tranzactii explicite
BEGIN TRAN;
SELECT @@TRANCOUNT;
INSERT INTO Cafele (nume, nr_shoturi, nivel_dulce) VALUES
('Latte',1,40);
SELECT * FROM Cafele;
SELECT @@TRANCOUNT;
COMMIT TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Cafele;
--imbricare a tranzactiilor
BEGIN TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Cafele;
BEGIN TRAN;
SELECT @@TRANCOUNT;
INSERT INTO Cafele (nume, nr_shoturi, nivel_dulce) VALUES
('cafea din tranzactia interioara',5,50);
SELECT * FROM Cafele;
COMMIT TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Cafele;
ROLLBACK TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Cafele;