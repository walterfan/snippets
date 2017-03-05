package com.github.walterfan;

import java.util.concurrent.TimeUnit;

import javax.ws.rs.client.Client;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import org.apache.http.client.HttpClient;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.impl.conn.PoolingClientConnectionManager;
import org.jboss.resteasy.client.jaxrs.ResteasyClient;
import org.jboss.resteasy.client.jaxrs.ResteasyClientBuilder;
import org.jboss.resteasy.client.jaxrs.engines.ApacheHttpClient4Engine;

import com.google.gson.Gson;
import com.google.gson.stream.JsonReader;

public class HttpUtil {
	private static final int MAX_PER_ROUTE_CONNECTIONS = 100;
	private static final int MAX_TOTAL_CONNECTIONS = 1000;
	
	public static Client createRestClient() {
		PoolingClientConnectionManager cm = new PoolingClientConnectionManager();
		// Increase max total connection to 1000
		cm.setMaxTotal(MAX_TOTAL_CONNECTIONS);
		// Increase default max connection per route to 100
		cm.setDefaultMaxPerRoute(MAX_PER_ROUTE_CONNECTIONS);
		
		HttpClient httpClient = new DefaultHttpClient(cm);
		ApacheHttpClient4Engine engine = new ApacheHttpClient4Engine(httpClient);
		ResteasyClient client = new ResteasyClientBuilder().httpEngine(engine)
				.establishConnectionTimeout(10, TimeUnit.SECONDS)
				.socketTimeout(5, TimeUnit.SECONDS)
				.build();
		return client;
	}


	
	public static void main(String[] args) {
		Client restClient = createRestClient();
		String url = "http://api.openweathermap.org/data/2.5/weather?q=milpita";
		Response resp = restClient.target(url)
				.request(MediaType.APPLICATION_JSON)
				 .get();;
		String jsonstring = resp.readEntity(String.class);
		System.out.println(jsonstring);
		
		
		resp.close();
		restClient.close();

	}

}
