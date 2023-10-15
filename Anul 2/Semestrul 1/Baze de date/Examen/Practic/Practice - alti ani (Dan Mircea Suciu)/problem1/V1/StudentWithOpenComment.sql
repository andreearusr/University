CREATE VIEW StudentWithOpenComment AS
SELECT DISTINCT name FROM Students, Grades, Comments WHERE cstatus = 1