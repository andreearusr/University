CREATE DATABASE Librarie;
GO
--folosim USE ca sa ne conectam la o anumita baza de date
USE Librarie;
/* comentariu
pe mai multe linii
*/
CREATE TABLE Carti
(cod_c INT PRIMARY KEY IDENTITY, --IDENTITY se foloseste pentru a genera in mod automat valori pentru coloana cod_c
titlu VARCHAR(100),
data_aparitiei DATE,
editura VARCHAR(80),
pret FLOAT
);
--adaugarea unei coloane intr-un tabel
ALTER TABLE Carti
ADD autor VARCHAR(100);--in acest caz vom stoca doar carti care au un singur autor
--modificarea tipului de date al unei coloane
ALTER TABLE Carti
ALTER COLUMN pret INT;
--stergerea unei coloane dintr-un tabel
ALTER TABLE Carti
DROP COLUMN autor;
--stergerea unui tabel din baza de date
DROP TABLE Carti;
--modificarea numelui bazei de date
ALTER DATABASE Librarie
MODIFY Name=Facultate;
--stergerea unei baze de date
USE master;
DROP DATABASE Facultate;
--crearea unei noi baze de date
CREATE DATABASE Florarie;
GO
USE Florarie;
--tabel cu constrangere unique
CREATE TABLE Flori
(cod_f INT PRIMARY KEY,
nume VARCHAR(100) UNIQUE --in acest caz se va genera un nume pentru constrangere de catre SQL Server
);
--stergerea unei constrangeri UNIQUE cu nume generat de catre SQL Server (!!!poate la voi se va genera un alt nume pentru constrangere)
ALTER TABLE Flori
DROP CONSTRAINT UQ__Flori__71F07D5AB33FA4B9;
