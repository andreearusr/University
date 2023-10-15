CREATE DATABASE Seminar4226SGBD;
GO
USE Seminar4226SGBD;
CREATE TABLE Becuri
(cod_b INT PRIMARY KEY IDENTITY,
model VARCHAR(100),
pret INT,
tip VARCHAR(100),
luminozitate INT,
temperaturaC INT,
producator VARCHAR(100),
curent VARCHAR(100)
);
INSERT INTO Becuri(model, pret, tip, luminozitate, temperaturaC,
producator, curent) VALUES ('Model de Neon din C310', 20,
'Neon',900, 4000,'Valoris','13W'),
('bec normal',2,'clasic',3000,2700,'No name','20W');
SELECT * FROM Becuri;
EXEC sp_lock;
SELECT DB_NAME(133)
SELECT * FROM sys.dm_tran_locks;
BEGIN TRAN;
SELECT * FROM Becuri;
SELECT * FROM sys.dm_tran_locks;
INSERT INTO Becuri (model, pret) VALUES ('bec tranzactional',
100);
SELECT * FROM Becuri;
SELECT * FROM sys.dm_tran_locks;
COMMIT TRAN;
SELECT * FROM Becuri;
SELECT * FROM sys.dm_tran_locks;
SELECT * FROM sys.dm_tran_active_transactions;
BEGIN TRAN;
SELECT * FROM sys.dm_tran_active_transactions;
SELECT * FROM Becuri;
SELECT * FROM sys.dm_tran_active_transactions;
COMMIT TRAN;
SELECT * FROM sys.dm_tran_active_transactions;
DBCC LOG (Seminar4226SGBD,2);