CREATE DATABASE Seminar5_226;
GO
USE Seminar5_226;
CREATE TABLE Persoane
(cod_p INT NOT NULL,
nume VARCHAR(100),
prenume VARCHAR(100),
localitate VARCHAR(100)
);
INSERT INTO Persoane (cod_p, nume, prenume, localitate) VALUES
(1,'Pop','Mihai','Oradea'), (-50,'Pop','Madalina','Sibiu'),
(23,'Popescu','Mihai','Resita'), (34,'Pop','Daniela','Arad'),
(234,'Ion','Ana','Craiova'), (-2, 'Pop','Adela','Floresti');
SELECT * FROM Persoane;
SELECT nume, prenume FROM Persoane WHERE nume='Pop';
GO
CREATE CLUSTERED INDEX IX_Persoane_cod_p_asc ON Persoane 
(cod_p ASC);
SELECT * FROM Persoane;
INSERT INTO Persoane (cod_p, nume, prenume, localitate) VALUES
(5,'Popescu','Maria','Oradea');
SELECT * FROM Persoane;
GO
DROP INDEX IX_Persoane_cod_p_asc ON Persoane;
GO
SELECT * FROM Persoane;
INSERT INTO Persoane (cod_p, nume, prenume, localitate) VALUES
(10, 'Pop','Adelina','Arad');
SELECT * FROM Persoane;
GO
CREATE CLUSTERED INDEX IX_Persoane_cod_p_asc ON Persoane
(cod_p ASC);
GO
SELECT * FROM Persoane;
DROP TABLE Persoane;
CREATE TABLE Persoane
(cod_p INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
prenume VARCHAR(100),
localitate VARCHAR(100),
popularitate INT
);
INSERT INTO Persoane (nume, prenume, localitate, popularitate) VALUES
('Pop','Ionut','Oradea',10), ('Pop','Daniel','Cluj-Napoca',8),
('Pop','Adina','Sibiu',4), ('Popescu','Adela','Arad',3),
('Popescu','Andrei','Brasov',10), ('Ion','Adrian','Sibiu',7),
('Pop','Andrei','Iasi',6);
SELECT * FROM Persoane;
GO
CREATE UNIQUE INDEX IX_Persoane_nume_asc_prenume_asc_uq ON Persoane
(nume ASC, prenume ASC);
GO
INSERT INTO Persoane (nume, prenume, localitate, popularitate) VALUES
('Pop','Adina','Oradea',10);
SELECT * FROM Persoane;
INSERT INTO Persoane (nume, prenume, localitate, popularitate) VALUES
('Ion','Angela','Arad',10), ('Alb','Alina','Arad',5);
INSERT INTO Persoane (nume, prenume, localitate, popularitate) VALUES
('Ion','Andrei','Oradea',1), ('Alb','Alina','Arad',5);
SELECT * FROM Persoane;
GO
DROP INDEX IX_Persoane_nume_asc_prenume_asc_uq ON Persoane;
GO
CREATE UNIQUE INDEX IX_Persoane_nume_asc_prenume_asc_uq ON Persoane
(nume ASC, prenume ASC) WITH (IGNORE_DUP_KEY = ON);
GO
INSERT INTO Persoane (nume, prenume, localitate, popularitate) VALUES
('Ion','Anamaria','Oradea',10), ('Pop','Adina','Oradea',5), 
('Ioan','Andrei', 'Braila',8), ('Popescu','Mihai','Oradea',6);
SELECT * FROM Persoane;
INSERT INTO Persoane (nume, prenume, localitate, popularitate) VALUES
('Pop',NULL,'Sibiu',10), (NULL, 'Andrei','Arad',8),
(NULL,NULL, 'Sinaia',8);
SELECT * FROM Persoane;
SELECT nume, prenume FROM Persoane WHERE nume='Pop';
SELECT nume, prenume FROM Persoane;
CREATE TABLE Dovleci
(cod_d INT NOT NULL, 
denumire VARCHAR(100),
pret INT
);
GO
CREATE CLUSTERED INDEX IX_Dovleci_cod_d_asc ON Dovleci 
(cod_d ASC);
GO
ALTER TABLE Dovleci 
ADD CONSTRAINT pk_Dovleci PRIMARY KEY (cod_d);
GO
--se foloseste indexul pentru sortare
SELECT nume, prenume FROM Persoane ORDER BY nume ASC, prenume ASC;
SELECT nume, prenume FROM Persoane ORDER BY nume DESC, prenume DESC;
SELECT nume, prenume FROM Persoane ORDER BY nume ASC;
SELECT nume, prenume FROM Persoane ORDER BY nume DESC;
--nu se foloseste indexul pentru sortare
SELECT nume, prenume FROM Persoane ORDER BY nume ASC, prenume DESC;
SELECT nume, prenume FROM Persoane ORDER BY nume DESC, prenume ASC;
SELECT nume, prenume FROM Persoane ORDER BY prenume ASC, nume ASC;
SELECT nume, prenume FROM Persoane ORDER BY prenume DESC, nume DESC;
SELECT nume, prenume FROM Persoane ORDER BY prenume ASC, nume DESC;
SELECT nume, prenume FROM Persoane ORDER BY prenume DESC, nume ASC;
SELECT nume, prenume FROM Persoane ORDER BY prenume ASC;
SELECT nume, prenume FROM Persoane ORDER BY prenume DESC;
GO
CREATE INDEX IX_Persoane_popularitate_filtered ON Persoane
(popularitate ASC) WHERE popularitate>4;
GO
--se foloseste indexul filtered
SELECT popularitate FROM Persoane WHERE popularitate>7;
SELECT DISTINCT popularitate FROM Persoane WHERE popularitate>4;
SELECT popularitate FROM Persoane WHERE popularitate BETWEEN 5 AND 9;
--nu se foloseste indexul
SELECT popularitate FROM Persoane;
SELECT popularitate FROM Persoane WHERE popularitate<5;
SELECT popularitate FROM Persoane WHERE popularitate BETWEEN 1 AND 4;
CREATE TABLE Categorii 
(cod_c INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);
CREATE TABLE Produse
(cod_p INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
cod_c INT FOREIGN KEY REFERENCES Categorii (cod_c)
);
INSERT INTO Categorii (nume) VALUES ('mancare'),('parfumuri'),
('pantofi'),('haine');
INSERT INTO Produse (nume, cod_c) VALUES ('pufuleti',1), ('ciocolata',1),
('Comme une Evidence',2), ('Naturelle',2);
DELETE FROM Categorii WHERE nume='pantofi';
GO
CREATE INDEX IX_Produse_cod_c_asc ON Produse (cod_c ASC);
GO
DELETE FROM Categorii WHERE nume='haine';
GO
--index cu clauza INCLUDE
ALTER TABLE Produse
ADD pret INT;
GO
CREATE INDEX IX_Produse_nume_asc_include_pret ON Produse
(nume ASC) INCLUDE (pret);
SELECT nume, pret FROM Produse;