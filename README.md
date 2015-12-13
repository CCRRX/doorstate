Doorstate
===========
by CRX 2015

UNAUFGERÄUMT UND QUICK AND DIRTY VERSION ... 

##TODO:
- Code aufräumen

##LETS START:

1. Am Pi an die pins (!REV2!)GPIO22 mit PIN17 (3,3V) ueber einen Schalter verbinden.<br>
2. Die "upload.php" kommt auf den Webserver <br>
3. Auf dem Pi die Dateien doorstate.cpp make.sh sha256.cpp sha256.h kopieren nach /root/doorstate <br>
4. Compilen mit ``` ./make.sh ```
5. Dann starten mit ```sudo ./gpiostatus```
6. Wer will mit dem in init.d einbinden


##FUNKTION:
- Zu Anfang wird der aktuelle Status hochgeladen.
- Jede Sekunde wird der Status abgefagt.
- Bei Änderung wird der Status neu hochgeladen.

Um Trollen entgegenzuwirken wird auf dem Pi eine random Zahl erzeugt, diese wird gesalzen (einfaches addieren) und gehasht.
Der Random und der Hash, sowie Status werden hochgeladen.

Der Webserver salzt mit dem spezial geheim Salz den Pin, macht ein Hash und prüft den mitgesendetet Hash, sind beide gleich 
wurde das gleiche Salz genutzt und der Status wird in die "Status.txt" auf dem Webserver geschrieben!


##ABHÄNGIGKEITEN:
```
pi@raspberrypi ~ $ sudo apt-get update
pi@raspberrypi ~ $ sudo apt-get install git-core 

pi@raspberrypi ~ $ git clone git://git.drogon.net/wiringPi
pi@raspberrypi ~ $ cd WiringPi
pi@raspberrypi ~/WiringPi $ ./build 
```
##SOURCE "UMBAUEN":

Nur g++ langt nicht...
```g++ sha256.cpp gpiostatus.cpp -o gpiostatus -lwiringPi```
oder einfach mit dem make.sh script

