 <?php
 /* Enunt: Un server genereaza un numar aleator. 
 Acesta primeste numere de la clienti si trimite clientului un mesaj (numar mai mic, mai mare sau egal cu numarul generat aleator). 
 La finalul jocului (dupa ce serverul trimite mesajul "EGAL"), serverul trimite clientului numarul de incercari.
	
 Rulare in doua terminale diferite:
	php server.php
	php client.php
 */ 
 $s = socket_create(AF_INET, SOCK_STREAM, 0);
 socket_connect($s , "127.0.0.1",8888);
 $mesaj="";
 while($mesaj!="EGAL"){
	$nr=readline("Dati un numar: ");
	socket_send($s, $nr, 100, 0);
	socket_recv($s,$mesaj,100,0);
	echo "Am primit de la server: $mesaj\n";
 }
 socket_recv($s,$incercari,100,0);
	echo "Am primit de la server: $incercari\n";
 socket_close($s);
?>