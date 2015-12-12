# doorstate
by CRX 2015

UNAUFGERAEUMT UND QUICK ND DIRTY VERSION ... 
BETA - ES FEHLT NOCH EIN WICHTIGER BESTANDTEIL FÃœR DNE DAUERBETRIEB

#TODO:

als service einbinden
code aufrÃ¤umen
________________________________

am pi an die pins (!REV2!)GPIO22 mit PIN17 (3,3V) ueber einen schalter verbinden.

die "upload.php" kommt auf den Webserver 

auf dem pi 
```c++
sudo ./gpiostatus
```


#FUNKTION:
zu anfang wird der aktuelle status hochgeladen
jede sekunde wird der status abgefagt
bei Ã¤nderung wird der status neu hochgeladen

um trollen entgegenzuwirken wird auf dem PI eine random zahl erzeugt, diese wird gesalzen (einfaches addieren) und gehascht.
der random und hash sowie status wird hochgeladen.

der webserver salzt mit dem spezial geheim salz den pin mcht ein hash und prÃ¼ft den mitgesendetet hash - sind beide gleich 
wurde das gleiche salz genutzt und der status wird nach status.txt auf dem webserver geschriben!


#ABHAENGIGKEITEN:
```shell
pi@raspberrypi ~ $ sudo apt-get update
pi@raspberrypi ~ $ sudo apt-get install git-core 

pi@raspberrypi ~ $ git clone git://git.drogon.net/wiringPi
pi@raspberrypi ~ $ cd WiringPi
pi@raspberrypi ~/WiringPi $ ./build 
```
SOURCE "UMBAUEN":

nur g++ langt nicht...
```shell
g++ sha256.cpp gpiostatus.cpp -o gpiostatus -lwiringPi
```
