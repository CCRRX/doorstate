# doorstate
by CRX 2015

UNAUFGERÄUMT UND QUICK AND DIRTY VERSION ... 
BETA - ES FEHLT NOCH EIN WICHTIGER BESTANDTEIL FÜR DNE DAUERBETRIEB

#TODO:

- Als service einbinden
- Code aufräumen
________________________________

1. Am pi an die pins (!REV2!)GPIO22 mit PIN17 (3,3V) ueber einen schalter verbinden.<br>
2. Die "upload.php" kommt auf den Webserver <br>
3. Auf dem pi <br>
```c++
sudo ./gpiostatus
```


#FUNKTION:
Zu Anfang wird der aktuelle Status hochgeladen.
Jede Sekunde wird der Status abgefagt.
Bei Änderung wird der Status neu hochgeladen.

Um trollen entgegenzuwirken wird auf dem PI eine random Zahl erzeugt, diese wird gesalzen (einfaches addieren) und gehasht.
Der Random und der Gash sowie Status wird hochgeladen.

Der webserver salzt mit dem spezial geheim Salz den Pin, macht ein Hash und prüft den mitgesendetet Hash - Sind beide gleich 
wurde das gleiche Salz genutzt und der Status wird nach Status.txt auf dem Webserver geschrieben!


#ABHÄNGIGKEITEN:
```shell
pi@raspberrypi ~ $ sudo apt-get update
pi@raspberrypi ~ $ sudo apt-get install git-core 

pi@raspberrypi ~ $ git clone git://git.drogon.net/wiringPi
pi@raspberrypi ~ $ cd WiringPi
pi@raspberrypi ~/WiringPi $ ./build 
```
SOURCE "UMBAUEN":

Nur g++ langt nicht...
```shell
g++ sha256.cpp gpiostatus.cpp -o gpiostatus -lwiringPi
```
