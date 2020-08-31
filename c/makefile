swap:
	gcc -g -o swap swap.c
	gcc -S swap.c
http_client:
	gcc -g -o http_client http_client.c
rot13:
	gcc -g -o rot13_server rot13_server.c
rot13_select:
	gcc	 -g -o rot13_server_select rot13_server_select.c
rot13_event:
	gcc	 -g -o rot13_server_event rot13_server_event.c -levent
rot13_event2:
	gcc	 -g -o rot13_server_event2 rot13_server_event2.c  -levent	
clean:
	rm -f swap swap.s http_client rot13_server rot13_server_select rot13_server_event rot13_server_event2
