USE [biblioteca]
GO
/****** Object:  StoredProcedure [dbo].[do_some]    Script Date: 1/27/2016 12:11:02 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER procedure [dbo].[do_some]
as
begin
create table autori(
 
	id int identity not null,
	nume varchar(30)

	constraint PK_autori primary key (id)

 )
 create table librarii(
	
	id int identity not null,
	nume varchar(30),
	adresa varchar(30),

	constraint PK_librarii primary key (id)
 )

create table domenii(
	
	id int identity not null,
	nume varchar(30),
	

	constraint PK_domenii primary key (id)
 )

 create table carti(
	
	id int identity not null,
	titlu varchar(30),
	id_domeniu int,
	id_librarie int,
	data_achizitie date,
	constraint FK_carte_domeniu foreign key (id_librarie) references domenii(id),
	constraint FK_carte_librarie foreign key (id_librarie) references librarii (id),
	constraint PK_carti primary key (id)
 )

 create table scrieri(
	
	id_carte int  not null,
	id_autor int not null,
	constraint FK_scrieri_autor foreign key (id_carte) references autori(id),
	constraint FK_scrieri_carte foreign key (id_autor) references carti(id),
	constraint PK_scrieri primary key (id_carte,id_autor)
 )

 ALTER procedure [dbo].[add_new]
@nume_autor varchar(30),
@id_carte int
as
begin
	if(not exists (select nume from autori where nume = @nume_autor))
		insert into autori (nume)
		values (@nume_autor)
	declare @id_autor varchar(30)
	select @id_autor = a.id from autori a where nume = @nume_autor

	

	if(exists (select s.id_autor from scrieri s where s.id_autor = @id_autor and s.id_carte = @id_carte))
		print 'Already have this association!!\n'
	else
		insert into scrieri (id_autor,id_carte)
		values (@id_autor,@id_carte)
end

--function
select l.nume,l.adresa,c.titlu,COUNT(s.id_carte) as NrAutori from carti c
inner join librarii l on 
l.id = c.id_librarie
inner join scrieri s
on s.id_carte = c.id
group by l.nume,l.adresa,c.titlu
having COUNT(s.id_carte) =2
order by c.titlu 

--view

select COUNT(C.id) as NR_CARTI  , l.nume from carti c
inner join librarii l
on c.id_librarie = l.id
where c.data_achizitie <= '2010-01-01'
group by l.nume
having COUNT(C.id) >= 5
order by l.nume desc
	

 end