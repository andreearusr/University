use examen
go

create table Clienti(
	id int identity not null primary key,
	nume varchar(30)
	);
go

create table Angajati(
	id int identity not null primary key,
	nume varchar(30)

	);
go

create table Marci(
	id int identity not null primary key,
	denumire varchar(30)
	);
go

create table Autovehicule(
	id int identity not null primary key,
	numar_inmatriculare varchar(30),
	motorizare varchar(30),
	id_marca int foreign key references Marci(id)
	);
go

create table Evidenta(
	id int identity not null primary key,
	id_angajat int foreign key references Angajati(id),
	id_client int foreign key references Clienti(id),
	id_autovehicul int foreign key references Autovehicule(id),
	data_inchiriere time,
	data_returnare time
	);
go
