create table user (
id identity,
username varchar(32),
password varchar(32) not null,
password_confirmation varchar(32) not null,
email varchar(32) not null,
enabled boolean
);