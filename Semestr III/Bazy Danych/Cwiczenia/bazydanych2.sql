create table person 
(
id number primary key,
lastname varchar2(15) not null,
firstname varchar2(15) not null,
secondname varchar2(15),
birthdate date not null,
gender char not null check (gender='m' or gender='f')
)

create table wages
(
  id number primary key,
  person_id number not null,
  fromwhen date not null,
  until date,
  wage number not null,
  constraint wages_fk foreign key(person_id) references person(id)
)

create table division
(
id number primary key,
person_id number not null,
name varchar(15) not null,
chief number(2),

constraint division_fk foreign key (person_id) references person(id)
);

create table employment
(
id number primary key,
person_id number not null,
division_id number not null,
fromwhen date not null,
until date,

constraint employment_fk_p foreign key(person_id) references person(id),
constraint employment_fk_dto foreign key(division_id) references division(id), 
);

create sequence tablename_i
  start with 1
  increment with 1
  order;
