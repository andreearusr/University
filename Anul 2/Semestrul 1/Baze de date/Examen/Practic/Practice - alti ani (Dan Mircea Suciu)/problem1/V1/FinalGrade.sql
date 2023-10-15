SELECT name, final = (SELECT SUM(grade)/COUNT(*) FROM Grades WHERE Grades.studentID = Students.studentID)
FROM STUDENTS