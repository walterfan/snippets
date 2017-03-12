#DROP TABLE IF EXISTS user;
CREATE TABLE user (
  user_id int(8) NOT NULL auto_increment,
  user_name varchar(32)  NOT NULL,
  password varchar(32)  NOT NULL,
  email varchar(64)  NOT NULL,
  phone_number varchar(32)  default NULL,
  user_status int(4) default 0,
  create_time timestamp NOT NULL default CURRENT_TIMESTAMP,
  last_modified_time timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (user_id)
);

CREATE UNIQUE INDEX user_email_idx on user (email);

#DROP TABLE IF EXISTS token;
CREATE TABLE token (
  token_id int(8) NOT NULL auto_increment,
  token_type int(4) default 0,
  token_value varchar(64)  NOT NULL,
  expiry_time timestamp NOT NULL,
  create_time timestamp NOT NULL default CURRENT_TIMESTAMP,
  last_modified_time timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (token_id)
);

#DROP TABLE IF EXISTS user_token;
CREATE TABLE user_token (
  user_id int(8) NOT NULL,
  token_id int(8) NOT NULL,
  create_time timestamp NOT NULL default CURRENT_TIMESTAMP,
  last_modified_time timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (user_id, token_id)
)