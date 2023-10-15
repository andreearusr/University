CREATE FUNCTION hasGrade (
	@studentID int,
	@taskID int
) RETURNS bit
AS
BEGIN
	DECLARE @result bit
	IF (0 = (SELECT COUNT(*) 
			FROM Grades 
			WHERE @studentID = studentID AND @taskID = taskID))
		SET @result=0
	ELSE
		SET @result= (SELECT gradeID FROM Grades 
			WHERE @studentID = studentID AND @taskID = taskID)
	RETURN @result
END

GO
CREATE PROCEDURE AssignGrade (
	@studentID int,
	@taskID int,
	@grade int,
	@comment varchar(256)
) AS
BEGIN
	DECLARE @gradeID int
	SET @gradeID = dbo.hasGrade(@studentID, @taskID)
	IF (@gradeID = 0)
	BEGIN
		INSERT INTO Grades (studentID, taskID, grade) VALUES (@studentID, @taskID, @grade)
		SET @gradeID = dbo.hasGrade(@studentID, @taskID)
	END
	ELSE
		UPDATE Grades SET grade=@grade WHERE studentID = @studentID and taskID = @taskID
	INSERT INTO Comments (gradeID, content) VALUES (@gradeID, @comment)
END