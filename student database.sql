create database school;
use school;
drop table student;
create table student(
id int primary key not null,
name varchar(15),
grade varchar(1),
percentage float

);
drop table admin;
create table admin(
id int auto_increment primary key,
username varchar(15) unique,
password varchar(20)
);
select * from admin;
select * from student;