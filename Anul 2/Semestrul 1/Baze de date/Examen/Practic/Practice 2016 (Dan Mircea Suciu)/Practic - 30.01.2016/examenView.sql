CREATE VIEW Castigatori
AS
SELECT TOP (100) PERCENT dbo.Jucatori.Nume, COUNT(*) AS NR
FROM     dbo.Jucatori INNER JOIN
                  dbo.Partide ON (dbo.Jucatori.ID = dbo.Partide.Jucator1 OR
                  dbo.Jucatori.ID = dbo.Partide.Jucator2 OR
                  dbo.Jucatori.ID = dbo.Partide.Castigator) AND dbo.Jucatori.ID = dbo.Partide.Castigator
GROUP BY dbo.Jucatori.Nume
ORDER BY NR DESC