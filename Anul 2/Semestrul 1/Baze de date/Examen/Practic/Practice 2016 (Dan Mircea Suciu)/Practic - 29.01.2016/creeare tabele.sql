use master 

IF exists ( SELECT * from sys.databases WHERE name = 'examen2')
	DROP database examen2

CREATE database examen2

GO

use examen2



create table Grupe(
	id int identity not null primary key,
	nume_grupa varchar(30),
);
go


create table Studenti(
	id int identity not null primary key,
	nume varchar(50),
	id_grupa int foreign key references Grupe(id),
	
);
go

create table Taskuri(
	id int identity not null primary key,
	nume varchar(50)
);
go

create table Note(
	id int identity not null primary key,
	nota int,
	id_task int foreign key references Taskuri(id),
	id_student int foreign key references Studenti(id),
);
go


create table Comentarii(
	id int identity not null primary key,
	stare varchar(50),
	id_nota int foreign key references Note(id),
);
go



