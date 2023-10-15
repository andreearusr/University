CREATE DATABASE Seminar1SGBD;
go
use Seminar1SGBD;

CREATE TABLE Cadouri
(cod_c INT PRIMARY KEY IDENTITY,
descriere VARCHAR(100),
valoare REAL,
posesor VARCHAR(100)
);

SELECT * FROM Cadouri;
