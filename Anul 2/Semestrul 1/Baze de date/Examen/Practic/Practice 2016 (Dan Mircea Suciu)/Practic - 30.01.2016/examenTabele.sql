use [Tenis];

if	 EXISTS (select * from sys.databases where name ='Tenis')
drop database Tenis;
create database Tenis;

create table Turnee 
(
ID int identity(1,1) not null,
Nume nvarchar(50),
Loc nvarchar(25),
DataStart datetime, 
DataEnd datetime,

constraint pk_Turnee primary key clustered (ID)
)

create table Jucatori
(
ID int identity(1,1) not null,
Nume nvarchar(50),
Punctaj int not null,
Valoare int not null,

constraint pk_Jucatori primary key clustered (ID)
)

create table Arene 
(
ID int identity(1,1) not null,
Nume nvarchar(25) not null,

constraint pk_Arene primary key clustered (ID)
)

create table Partide 
(
ID int identity(1,1) not null,
Jucator1 int,
Jucator2 int,
ArenaID int,
TurneuID int,
Ora datetime,
Castigator int not null,
Puncte1 int, 
Puncte2 int,
Valoare1 int, 
Valoare2 int, 

constraint pk_Partide primary key clustered (ID) 
)

alter table Partide with check
add constraint FK_Jucator1 foreign key (Jucator1) references Jucatori(ID)

alter table Partide with check
add constraint FK_Jucator2 foreign key (Jucator2) references Jucatori(ID)

alter table Partide with check
add constraint FK_Arene foreign key (ArenaID) references Arene(ID)

alter table Partide with check
add constraint FK_Turnee foreign key (TurneuID) references Turnee(ID)

alter table Partide with check
add constraint FK_Castigator foreign key (Castigator) references Jucatori(ID)
