use examen
go

CREATE FUNCTION [dbo].[Libere] 
(
@DataOraLibera datetime
)
RETURNS TABLE
AS
RETURN(
SELECT dbo.Autovehicule.NrInmatriculare, dbo.Autovehicule.TipMotorizare, dbo.Marci.Denumire
FROM dbo.Evidente INNER JOIN
dbo.Autovehicule ON dbo.Evidente.AutovehiculID = dbo.Autovehicule.ID INNER JOIN
dbo.Marci ON dbo.Marci.ID = dbo.Autovehicule.Marca
WHERE @DataOraLibera NOT BETWEEN dbo.Evidente.DataOraInchiriere AND dbo.Evidente.DataOraReturnare
)