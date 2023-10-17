 <?php
/* Enunt: Un server genereaza un numar aleator. 
Acesta primeste numere de la clienti si trimite clientului un mesaj (numar mai mic, mai mare sau egal cu numarul generat aleator). 
La finalul jocului (dupa ce serverul trimite mesajul "EGAL"), serverul trimite clientului numarul de incercari.
	
 Rulare in doua terminale diferite:
	php server.php
	php client.php
 */ 
 
 function execute_task($c,$nr,$rand) {
	 $mic="MAI MIC";
 $mare="MAI MARE";
 $egal="EGAL";
 $incercari=0;
  while($nr!=$rand){
 socket_recv($c,$nr,100,0);
 echo "Am primit de la client $nr.\n";
 if($nr<$rand) 	{socket_send($c, $mic, strlen($mic), 0);$incercari++;}
 if($nr>$rand) 	{socket_send($c, $mare, strlen($mare), 0);$incercari++;}
 if($nr==$rand) {socket_send($c, $egal, strlen($egal), 0); echo "Clientul a ghicit din $incercari incercari\n";socket_send($c, $incercari, 100, 0);}
 }
}
 
 $rand=rand(0,99);
 echo "Am generat $rand\n";
 
 $s = socket_create(AF_INET,SOCK_STREAM,0);
 socket_bind($s,"127.0.0.1",8888);
 socket_listen ($s,5);
 while(1)
 {
 $incercari=1;
 $c = socket_accept($s);
 $nr=-1;
 
 $pid = pcntl_fork();
 if ($pid == 0) {
    execute_task($c,$nr,$rand);
    exit();
  }
 
 
 
 
 }
 socket_close($s);
 ?>