-- ================================================
-- Template generated from Template Explorer using:
-- Create Inline Function (New Menu).SQL
--
-- Use the Specify Values for Template Parameters 
-- command (Ctrl-Shift-M) to fill in the parameter 
-- values below.
--
-- This block of comments will not be included in
-- the definition of the function.
-- ================================================
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
ALTER FUNCTION Punctaj
(	
	@JucatorID int
)
RETURNS TABLE 
AS
RETURN 
(
	SELECT Castigator, Nume, (SUM(Puncte1) + Punctaj) AS P, (SUM(Valoare1) + Valoare) AS V
	FROM Partide inner join Jucatori on Jucatori.ID = Castigator
	WHERE Castigator = @JucatorID
	GROUP BY Castigator, Nume, Punctaj, Valoare

)

GO
