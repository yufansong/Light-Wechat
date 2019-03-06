drop database if exists db1651459;

create database db1651459;

use db1651459;

create table user
(
	userName varchar(20) primary key,
	password varchar(50) not null,
	scanMessageNum integer,
	online tinyint(1),
	isFirstLogin tinyint(1)
);

create table information
(
	messageID integer primary key,
	sendName varchar(20),
	receiveName varchar(20),
	message varchar(970),
	isFile tinyint(1)
);

insert into information value(1,'ZhangSan','LiSi','Hello World!',0);
insert into information value(2,'ZhangSan','WangWu','Hello World!',0);
insert into information value(3,'LiSi','ZhangSan','Hello World,too!',0);
