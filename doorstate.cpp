//WiringPi-Api einbinden
#include <wiringPi.h>

//Rest einbinden
#include <iostream>
#include "sha256.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <curl/curl.h>

using namespace std;


template <typename T>
string to_string(T value)
{
        ostringstream os ;
        os << value ;
        return os.str() ;
}

int send(string status){
int random = 000000;
int salt  = 12345678; //Das ist eine Art Passwort und muss gleich auf dem Pi und in der PHP Datei sein!

srand (time(NULL));		//Random Zeug
random = rand() % 9999 + 10000; //Random Nummer erzeugen 100000 bis 999999

string input;
input = to_string(random + salt); //Nur Strings können gehasht werden und random wird gesalzen durch addition

string hash = sha256(input); //Hashpower!

stringstream sstr;
sstr << "hash=" << hash << "&pin=" << random << "&status=" << status;
string befehl = sstr.str();


	//ab hier wird hochgeladen - Code von irgeneinem Beispiel kopiert
  CURL *curl;
  CURLcode res;

	const char* postthis = befehl.c_str();


  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "webseite.com/doorstate/setdorstate.php");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);

    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
       itself */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }


}


int main()
{

int last = 2;   //Zum Start gleich null setzten ist doof, villeicht ist der Status noch nicht gemeldet
                //dh. Sensor sagt 0 und auf der Webseite ist noch der alte Wert 1 angezeigt, daher einmal Alles melden

        //Starte die WiringPi-Api (wichtig)
        if (wiringPiSetup() == -1)
        return 1;

	//Ja sind mehr als nötig, einer langt aber 3 sind auch gut, wer weiß was noch dazu kommt :>
        //Schalte GPIO 17 (=WiringPi Pin 0) auf Eingang
        pinMode(0, INPUT);

        //Schalte GPIO 27 (=WiringPi Pin 2) auf Eingang
        pinMode(2, INPUT);

        //Schalte GPIO 22 (=WiringPi Pin 3) auf Eingang
        pinMode(3, INPUT);


        //Dauerschleife
        while(1) {
        delay(1000); //Bremseeee ...

        //GPIO lesen
        if(digitalRead(3)==1 && (last == 0 || last == 2)) {
                printf("Geschlossen\n");
                //status = "geschlossen";
                send("geschlossen");
                last = 1;
                delay(1000); //noch eine Bremse ... Macht kein Sinn aber bremsen stören hier ja nicht
        }
        if(digitalRead(3)==0 && (last == 1 || last == 2)){
                printf("Geöffnet\n");
                //status = "offen";
                send("offen");
                last = 0;
                delay(1000); //noch eine Bremse ... Nacht kein Sinn aber Bremsen stören hier ja nicht
        }
}
return 0;
}

