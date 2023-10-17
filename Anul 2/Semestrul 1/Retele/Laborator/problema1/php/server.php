 <?php
 /* Enunt: Clientul trimite serverului un numar. Serverul il primeste si il afiseaza pe ecran.
	
 Rulare in doua terminale diferite:
	php server.php
	php client.php
 */ 
 $s = socket_create(AF_INET,SOCK_STREAM,0);
 socket_bind($s,"127.0.0.1",8888);
 socket_listen ($s,5);
 while(1)
 {
 $c = socket_accept($s);
 socket_recv($c,$nr,100,0);
 echo "Am primit de la client $nr\n";
 }
 socket_close($s);
 ?>