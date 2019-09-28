package com.github.walterfan.userservice;

import org.flywaydb.core.Flyway;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class DemoApplication {

	@Value("${spring.datasource.url}")
	private String url;

	@Value("${spring.datasource.username}")
	private String username;

	@Value("${spring.datasource.password}")
	private String password;

	@Value("${connect.database}")
	private String database;

	public static void main(String[] args) {
		SpringApplication.run(DemoApplication.class, args);
	}

	@Bean(initMethod = "migrate")
	public Flyway flyway() {
		String urlWithoutDbName = url.substring(0, url.lastIndexOf("/"));
		Flyway flyway = new Flyway();
		flyway.setDataSource(urlWithoutDbName, username, password);
		flyway.setSchemas(database);
		flyway.setBaselineOnMigrate(true);
		return flyway;
	}
}
