USE master
GO
IF(EXISTS(SELECT * FROM sys.databases WHERE name='P162022'))
	DROP DATABASE P162022;
GO
CREATE DATABASE P162022;
GO
USE P162022;
GO
CREATE TABLE Bijutieri
(cod_b INT PRIMARY KEY IDENTITY,
nume_b VARCHAR(100),
tara_de_origine VARCHAR(100)
);
CREATE TABLE MetalePretioase
(cod_m INT PRIMARY KEY IDENTITY,
nume_m VARCHAR(100),
descriere_m VARCHAR(100)
);
CREATE TABLE Inele
(cod_i INT PRIMARY KEY IDENTITY,
model_i VARCHAR(100),
pret REAL,
marime INT,
verigheta BIT,
cod_b INT FOREIGN KEY REFERENCES Bijutieri(cod_b)
ON UPDATE CASCADE ON DELETE CASCADE,
cod_m INT FOREIGN KEY REFERENCES MetalePretioase(cod_m)
ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE PietrePretioase
(cod_p INT PRIMARY KEY IDENTITY,
nume_p VARCHAR(100)
);
CREATE TABLE Distributie
(cod_i INT FOREIGN KEY REFERENCES Inele(cod_i)
ON UPDATE CASCADE ON DELETE CASCADE,
cod_p INT FOREIGN KEY REFERENCES PietrePretioase(cod_p)
ON UPDATE CASCADE ON DELETE CASCADE,
nr_pietre INT,
CONSTRAINT pk_Distributie PRIMARY KEY (cod_i,cod_p)
);
--Bijutieri
INSERT INTO Bijutieri (nume_b, tara_de_origine) VALUES
('bijutier1','Turcia');
INSERT INTO Bijutieri (nume_b, tara_de_origine) VALUES
('bijutier2','India');
INSERT INTO Bijutieri (nume_b, tara_de_origine) VALUES
('bijutier3','Spania');
--MetalePretioase
INSERT INTO MetalePretioase (nume_m,descriere_m) VALUES 
('aur','descriere aur');
INSERT INTO MetalePretioase (nume_m,descriere_m) VALUES 
('argint','descriere argint');
INSERT INTO MetalePretioase (nume_m,descriere_m) VALUES 
('platina','descriere platina');
--Inele bijutier1
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel1',200,8,1,1,1);
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel2',100,6,0,1,1);
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel3',400,9,0,1,1);
--Inele bijutier2
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel4',100,8,0,2,2);
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel5',100,9,0,2,2);
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel6',400,7,0,2,2);
--Inele bijutier3
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel7',2000,8,0,3,3);
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel8',1000,7,0,3,3);
INSERT INTO Inele(model_i,pret,marime,verigheta,cod_m,cod_b) VALUES
('inel9',4000,6,0,3,3);
--PietrePretioase
INSERT INTO PietrePretioase (nume_p) VALUES ('diamant');
INSERT INTO PietrePretioase (nume_p) VALUES ('rubin');
INSERT INTO PietrePretioase (nume_p) VALUES ('smarald');
--Distributie
INSERT INTO Distributie (cod_i,cod_p,nr_pietre) VALUES (3,1,3);
INSERT INTO Distributie (cod_i,cod_p,nr_pietre) VALUES (3,2,7);
INSERT INTO Distributie (cod_i,cod_p,nr_pietre) VALUES (2,3,1);

SELECT * FROM Bijutieri
SELECT * FROM Inele
SELECT * FROM MetalePretioase