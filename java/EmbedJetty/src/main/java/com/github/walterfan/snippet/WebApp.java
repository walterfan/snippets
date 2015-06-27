package com.github.walterfan.snippet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Handler;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.eclipse.jetty.server.handler.ContextHandler;
import org.eclipse.jetty.server.handler.ContextHandlerCollection;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;

class HelloServlet extends HttpServlet
{
    private String greeting="Hello ctx0";
    public HelloServlet(){}
    public HelloServlet(String greeting)
    {
        this.greeting=greeting;
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        response.setContentType("text/html");
        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().println("<h1>"+greeting+"</h1>");
        response.getWriter().println("session=" + request.getSession(true).getId());
    }
}


class HelloHandler extends AbstractHandler
{
    public void handle(String target,Request baseRequest,HttpServletRequest request,HttpServletResponse response) 
        throws IOException, ServletException
    {
        response.setContentType("text/html;charset=utf-8");
        response.setStatus(HttpServletResponse.SC_OK);
        baseRequest.setHandled(true);
        response.getWriter().println("<h1>Hello ctx1</h1>");
    }
}

public class WebApp 
{

    
    public static void main(String[] args) throws Exception
    {
        Server server = new Server(8080);
 
        ServletContextHandler context0 = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context0.setContextPath("/ctx0");
        context0.addServlet(new ServletHolder(new HelloServlet()),"/*");
        context0.addServlet(new ServletHolder(new HelloServlet("Buongiorno Mondo")),"/it/*");
        context0.addServlet(new ServletHolder(new HelloServlet("Bonjour le Monde")),"/fr/*");
 

        
        ContextHandler context1 = new ContextHandler();
        context1.setContextPath("/ctx1");
        context1.setResourceBase(".");
        context1.setClassLoader(Thread.currentThread().getContextClassLoader());
        context1.setHandler(new HelloHandler());
 
        ContextHandlerCollection contexts = new ContextHandlerCollection();
        contexts.setHandlers(new Handler[] { context0, context1 });
 
        server.setHandler(contexts);
 
        server.start();
        server.join();
    }
}
