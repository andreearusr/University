-- ================================================
-- Template generated from Template Explorer using:
-- Create Procedure (New Menu).SQL
--
-- Use the Specify Values for Template Parameters 
-- command (Ctrl-Shift-M) to fill in the parameter 
-- values below.
--
-- This block of comments will not be included in
-- the definition of the procedure.
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
ALTER PROCEDURE AdaugaPartida
	@TurneuID nvarchar(50), 
	@Jucator1ID nvarchar(50),
	@Jucator2ID nvarchar(50),
	@Puncte1 int,
	@Puncte2 int,
	@Valoare1 int,
	@Valoare2 int,
	@CastigatorID nvarchar(50),
	@ArenaID int,
	@Data datetime
AS
BEGIN
	INSERT INTO Partide VALUES (@Jucator1ID, @Jucator2ID, @ArenaID, @TurneuID, @Data, @CastigatorID, @Puncte1, @Puncte2, @Valoare1, @Valoare2)
END
GO
