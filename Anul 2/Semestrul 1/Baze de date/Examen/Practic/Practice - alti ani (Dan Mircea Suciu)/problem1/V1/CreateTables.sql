--CREATE TABLE Groups (
--	groupID int IDENTITY(1,1) NOT NULL PRIMARY KEY,
--	name varchar(8)
--) GO

CREATE TABLE Students (
	studentID int IDENTITY(1,1) NOT NULL PRIMARY KEY,
	name varchar(64),
	groupName varchar(8),	
	--FOREIGN KEY (groupID) REFERENCES Groups(groupID)
);
GO

CREATE TABLE Tasks (
	taskID int IDENTITY(1,1) NOT NULL PRIMARY KEY,
	name varchar(64)
);
GO

CREATE TABLE Grades (
	gradeID int IDENTITY(1,1) NOT NULL PRIMARY KEY,
	studentID int,
	taskID int,
	grade int,
	FOREIGN KEY (studentID) REFERENCES Students(studentID),
	FOREIGN KEY (taskID) REFERENCES Tasks(taskID)
);
GO

CREATE TABLE Comments (
	commentID int IDENTITY(1,1) NOT NULL PRIMARY KEY,
	gradeID int,
	content varchar(256), 
	cstatus bit,
	FOREIGN KEY (gradeID) REFERENCES Grades(gradeID)
);
GO