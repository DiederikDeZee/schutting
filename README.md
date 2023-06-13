# Schutting Device Driver

### Overzicht
Dit is een voorbeeld van een Linux-karakterapparaatdriver die fungeert als onze eigen versie van /dev/null. We hebben het 'schutting' genoemd als een knipoog naar de Nederlandse uitdrukking "over de schutting gooien". Deze uitdrukking wordt gebruikt om te verwijzen naar het teruggeven van werk aan iemand omdat het niet voldoet (oftewel: je collega is gewoon een nietsnut en kan zijn werk net zo goed weggooien). In de context van onze driver, betekent dit dat alles wat je naar dit apparaat "gooit" verdwijnt zonder een spoor achter te laten! Wow! ✨😮

*Note*: Onthoud dat dit een grap is en niet bedoeld voor serieus gebruik. Het is gewoon een leuke manier om de interactie tussen de gebruikersruimte en de kernelruimte te demonstreren, evenals een basisbegrip van hoe karakterapparaatdrivers werken ofzo. Dus klaag me niet aan als je bestanden foetsie zijn :(.


### Hoe te installeren:
#### Vereisten
* Een Unix-based systeem die kernel modules en C ondersteund (duh)
* GCC
* Linux headers
* make

#### Installatie
1. Clone de repository en ga de map in:
```
git clone git@github.com:DiederikDeZee/schutting.git
cd schutting-driver
```

2. Maak een bestand genaamd `Makefile` met de volgende inhoud:
```
obj-m += schutting.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

3. Compileer en laad de kernel module in: 
```
make
insmod schutting.ko
```



### Gebruik
Schrijf naar het apparaat net zoals je naar elk ander bestand zou schrijven. Hier is een voorbeeld:

```
echo "Hallo, wereld!" > /dev/schutting
```

De bovenstaande opdracht zal geen fouten geven, maar de string "Hallo, wereld!" wordt nergens opgeslagen. Het is "over de schutting gegooid"!

Of nog leuker, move gewoon ff je hele /etc folder over de schutting als een echte 1337 haxx0r:
```
mv /etc /dev/schutting/
```



### Verwijderen
Verwijder de module als volgt:
```
sudo rmmod schutting
```

Daarna kan je de build-artefacten opschonen:

```
make clean
```


### Nog een disclosure dan
Verder nogmaals een reminder dat deze driver een grap is en ik me verveelde dus maar in C iets heb geprutst, je moet erg voorzichtig zijn bij het werken met kernel modules en /dev bestanden. Run dit **NOOIT!** op productie.
