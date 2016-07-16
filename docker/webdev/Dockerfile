FROM centos:latest
MAINTAINER Walter Fan "walter.fan@gmail.com"
ENV REFRESHED_AT 2016-07-01

RUN yum update -y
RUN yum install -y maven

RUN mkdir -p /var/www/html/website
ADD nginx/global.conf /etc/nginx/conf.d/
ADD nginx/nginx.conf /etc/nginx/

EXPOSE 80
