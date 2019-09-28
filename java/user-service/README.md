

spring init --java-version=1.8 --dependencies=web,actuator,devtools,jpa,flyway --packaging=jar --groupId=com.github.walterfan --artifactId=user-service

mvn spring-boot:run

mysql> create database userservice  CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci; 

mysql> create user 'walter'@'%' identified by 'password'; 

mysql> grant all on userservice.* to 'walter'@'%'; 

mysql> use useservice;

mysql> show tables;
+-----------------------+
| Tables_in_userservice |
+-----------------------+
| address               |
| flyway_schema_history |
| user_detail           |
+-----------------------+
3 rows in set (0.00 sec)

mysql> desc address;
+----------------+--------------+------+-----+-------------------+-------------------+
| Field          | Type         | Null | Key | Default           | Extra             |
+----------------+--------------+------+-----+-------------------+-------------------+
| id             | int(11)      | NO   | PRI | NULL              | auto_increment    |
| user_id        | char(36)     | NO   | MUL | NULL              |                   |
| city           | varchar(25)  | NO   |     | NULL              |                   |
| address_line_1 | varchar(250) | NO   |     | NULL              |                   |
| address_line_2 | varchar(250) | YES  |     | NULL              |                   |
| zip_code       | char(6)      | NO   |     | NULL              |                   |
| create_time    | timestamp    | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
| update_time    | timestamp    | YES  |     | NULL              |                   |
+----------------+--------------+------+-----+-------------------+-------------------+
8 rows in set (0.01 sec)

mysql> desc user_detail;
+--------------+--------------+------+-----+-------------------+-------------------+
| Field        | Type         | Null | Key | Default           | Extra             |
+--------------+--------------+------+-----+-------------------+-------------------+
| id           | int(11)      | NO   | PRI | NULL              | auto_increment    |
| user_id      | char(36)     | NO   | MUL | NULL              |                   |
| first_name   | varchar(250) | NO   |     | NULL              |                   |
| last_name    | varchar(250) | NO   |     | NULL              |                   |
| email        | varchar(250) | NO   |     | NULL              |                   |
| phone_number | varchar(250) | NO   |     | NULL              |                   |
| create_time  | timestamp    | YES  |     | CURRENT_TIMESTAMP | DEFAULT_GENERATED |
| update_time  | timestamp    | YES  | MUL | NULL              |                   |
+--------------+--------------+------+-----+-------------------+-------------------+
8 rows in set (0.00 sec)

# Reference
* https://flywaydb.org/