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


$pin = $pin + 12345678; 		//Salzen bzw. Passwort addieren


$context = hash_init("sha256"); 	//Hier wird der Hash aus dem gesalzenen Pin erzeugt
hash_update($context, $pin);
$finalshit =  hash_final($context). "\n";

if($hash == $finalshit){		//Wenn gesendeteter Hash und erzeugter überienstimmt wird der Inhalt analysiert
$statusfile = fopen('status.txt', 'w');	//die Statusdatei öffen
if($status == "geschlossen\n"){ 	//Man soll ja nicht direkt mit dem Argument in die Datei schreiben können
fwrite($statusfile,"geschlossen");
echo "AuThEnTiFiZiErT - und hochgeladen :>\n";
}

elseif($status == "offen\n"){
fwrite($statusfile,"offen");
echo "AuThEnTiFiZiErT - und hochgeladen :>\n";
}
else{					//Wenn versucht wird etwas anderes als offen oder geschlossen zu schrieben gibt es ein error
echo "Nope\n";
}
fclose($statusfile);
}
?>
