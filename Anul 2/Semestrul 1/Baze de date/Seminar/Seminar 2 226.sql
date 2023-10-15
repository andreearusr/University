CREATE DATABASE Seminar2_226;
GO
USE Seminar2_226;
CREATE TABLE Persoane
(cod_p INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
prenume VARCHAR(100),
localitate VARCHAR(70)
);
INSERT INTO Persoane (nume, prenume, localitate) VALUES
('Pop','Andrei','Oradea'), ('Pop','Adina','Oradea'), ('Pop','Mihai','Floresti'),
('Ion','Vasile','Sibiu'), ('Ion','Anna',NULL);

SELECT * FROM Persoane;

ALTER TABLE Persoane
ADD CONSTRAINT uq_nume_prenume UNIQUE (nume, prenume);

INSERT INTO Persoane (nume, prenume, localitate) VALUES
('Ion','Oana','Paris'), ('Ion','Vasile','Brasov');

SELECT * FROM Persoane;

UPDATE Persoane SET nume='Popescu',localitate='Mangalia' WHERE
nume='Pop' AND prenume='Andrei';

SELECT * FROM Persoane;

DELETE FROM Persoane WHERE localitate IS NULL;

SELECT * FROM Persoane;

SELECT  nume FROM Persoane;

SELECT DISTINCT nume FROM Persoane;

INSERT INTO Persoane (nume, prenume, localitate) VALUES ('Pop','Maria','Oradea');

SELECT nume, localitate FROM Persoane;

SELECT DISTINCT nume, localitate FROM Persoane;
--interogare ce contine o coloana cu valoare calculata, care are si un alias - [cod dublat]
SELECT nume, prenume, cod_p, cod_p * 2 AS [cod dublat] FROM Persoane;
--se returneaza inregistrarile pentru care prenumele incepe cu M, A sau P
SELECT * FROM Persoane WHERE prenume LIKE '[map]%';

SELECT prenume FROM Persoane WHERE prenume < 'm';

SELECT nume FROM Persoane WHERE nume > 'm';
--am redenumit coloana localitate in oras la nivelul interogarii
SELECT localitate AS oras FROM Persoane;

--relatie one to many
CREATE TABLE Categorii
(cod_c INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);
CREATE TABLE Produse
(cod_p INT PRIMARY KEY IDENTITY,
denumire VARCHAR(100),
pret FLOAT,
cod_c INT FOREIGN KEY REFERENCES Categorii(cod_c)
);

INSERT INTO Categorii (nume) VALUES ('mancare'), ('bautura'), ('pantofi'),
('haine');
INSERT INTO Produse (denumire, pret, cod_c) VALUES
('chec',10,1), ('burger',17,1), ('cola',5,2), ('vin',20,2), ('cizme',200,3),
('carte',30,NULL);

SELECT * FROM Categorii;
SELECT * FROM Produse;

--afisam inregistrarile care au o potrivire in celalalt tabel
SELECT * FROM Categorii C INNER JOIN Produse P ON C.cod_c=P.cod_c;
--afisam toate inregistrarile din tabelul de pe partea stanga, indiferent
--daca au sau nu potriviri in tabelul din partea dreapta
SELECT * FROM Categorii C LEFT JOIN Produse P ON C.cod_c=P.cod_c;
--afisam toate inregistrarile din tabelul de pe partea dreapta, indiferent
--daca au sau nu potriviri in tabelul din partea stanga
SELECT * FROM Categorii C RIGHT JOIN Produse P ON C.cod_c=P.cod_c;
--afisam toate inregistrarile din ambele tabele, indiferent daca au sau nu 
--potriviri 
SELECT * FROM Categorii C FULL JOIN Produse P ON C.cod_c=P.cod_c;

--afisam numarul de produse si pretul total pentru fiecare cod de categorie
SELECT cod_c, COUNT(cod_p) AS [nr produse], SUM(pret) AS [pret pe categorie]
FROM Produse
GROUP BY cod_c;

--afisam numarul de produse si pretul total pentru fiecare cod de categorie
--pentru care pretul total este > 25
SELECT cod_c, COUNT(cod_p) AS [nr produse], SUM(pret) AS [pret pe categorie]
FROM Produse
GROUP BY cod_c
HAVING SUM(pret) > 25;

--afisam categoriile care au produse
SELECT nume FROM Categorii WHERE cod_c IN (SELECT cod_c FROM Produse);
--varianta cu JOIN
SELECT DISTINCT C.nume FROM Categorii C INNER JOIN Produse P ON C.cod_c=P.cod_C;
--varianta cu EXISTS 
SELECT C.nume FROM Categorii C WHERE EXISTS (SELECT * FROM Produse P
WHERE C.cod_c=P.cod_c);
--afisam categoriile care nu au produse
SELECT nume FROM Categorii WHERE cod_c NOT IN (SELECT cod_c FROM Produse
WHERE cod_c IS NOT NULL);
--varianta cu NOT EXISTS
SELECT C.nume FROM Categorii C WHERE NOT EXISTS (SELECT * FROM Produse P WHERE
C.cod_c=P.cod_c);
--varianta cu EXCEPT
SELECT nume FROM Categorii
EXCEPT
SELECT C.nume FROM Categorii C INNER JOIN Produse P ON C.cod_c=P.cod_c;
--codurile tuturor categoriilor 
SELECT cod_c FROM Categorii
UNION
SELECT cod_c FROM Produse;

