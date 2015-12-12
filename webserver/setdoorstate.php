<?php
//Für debugging nicht auskommentieren
/*
echo $_POST['pin']."\n";
echo $_POST['status']."\n";
echo $_POST['hash']."\n";
*/

$status = $_POST['status'] . "\n"; 	//Die drei Variabeln einlesen!
$hash = $_POST['hash'] . "\n"; 		//Das \n einfach ignorieren und da lassen!
$pin = $_POST['pin'] . "\n";


$pin = $pin + 13374223; 		//Salzen bzw. passwort addieren


$context = hash_init("sha256"); 	//Hier wird der Hash aus dem gesalzenen pin erzeugt
hash_update($context, $pin);
$finalshit =  hash_final($context). "\n";

if($hash == $finalshit){		//Wenn gesendeteter hash und erzeugter überienstimmt wird der inhalt analysiert
$statusfile = fopen('status.txt', 'w');	//die satus datei öffen
if($status == "geschlossen\n"){ 	//man soll ja nicht direkt mit dem Argument in die datei schrieben können
fwrite($statusfile,"geschlossen");
echo "AuThEnTiFiZiErT - und hochgeladen :>\n";
}

elseif($status == "offen\n"){
fwrite($statusfile,"offen");
echo "AuThEnTiFiZiErT - und hochgeladen :>\n";
}
else{					//Wenn versucht wird was anderes als offen oder geschlossen zu schrieben gibts ein error
echo "Nope\n";
}
fclose($statusfile);
}
?>
