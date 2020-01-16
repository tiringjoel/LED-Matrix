README(WinAVR-MiniHOWTO).txt
****************************
M. Meier, 12.7.05

Zur Softwareerstellung fuer AVR-Controller bieten sich folgende Moelichkeiten an:

- C:
	-> Fuer etwas anspruchsvollere Projekte ist die Open Source "WinAVR" resp. "AVRGCC"  unbedingt empfehlenswert!
	     WinAVR ist dabei ein "Bundle" mit C-Compiler 'AVRGCC', Editor 'Programmers Notepad', Programmer-SW 'Averdude' etc.
	     Am Besten studiert man nach Installation das Demo-Beispiel:   C:\WinAVR\examples\demo\...

	-> Wem die Initialisierung der Peripherie in WinAVR zu kompliziert ist, hat mit  "CodeVision AVR" eine Alternative:
	     mittels einiger Mausclicks kann mit dieser integrierten Entwicklungsumgebung die Mikrocontroller-Peripherie
	     konfigurieren, resp. den entsprechenden C-Code generieren lassen. 
	     "CodeVision AVR" ist jedoch nicht "OpenSource" und hat deshlab eine Codebegrenzung auf 2KB Programmcode!
	     Bei nachtr�lichem Umstieg auf AVRGCC ist eine �erarbeitung n�ig, da I/O im C-Code anders angesprochen wird. 

- Assembler:
	-> Assembler sollte aber verwendet werden wenn der C-Compiler zuwenig effizient ist!
	     Mittels Atmels AStudio4 l�st sich in Assembler konfortabel entwickeln uns simulieren. 

	     

Programmierung eines AVR-Controllers:

Die Atmel-Controller sind 'In-System Programmable' (ISP), lassen sich also in der eigenen Schaltung eingebaut programmiereren.
Dazu benoeigt man nur ein ein Programmierkabel vom Parallelport des PCs zur eigenen Schaltung, wobei auf dieser ein Stecker angebracht wird.
Folgende Programmiersoftware und Programmierkabel hat sich bew�rt:

	-> "AVRDUDE", in WinAVR bereits enthalten.

	- ebenfalls in WinAVR enthalten w�e zudem die Programmiersoftware UISP, hab sie aber nicht getestet.
	- nicht mehr aktuell da neuere Bausteine nicht mehr untersttzt werden ist meine eigene Programmer-Software "PrgAvr*.exe"


AVRDUDE unterstuetzt verschiedene Programmierkabel. Im Folgenden wird die Konfiguration "bsd" verwendet:

Dazu folgendes Programmierkabel vom PC-Parallelport auf  eine z.B. 5-polige Buchsenleiste herstellen (es sind auch andere Steckerbelegungen gaegig):
 
PC-Parallelport (DB25)         Programmierstecker AVR (5-pol. Buchsenleiste)
	  9 -------------------[]-- (1) MOSI
	 18 ----------------------- (2) GND
	  7 -------------------[]-- (3) /RST
	  8 -------------------[]-- (4) SCK 
	 10 -------------------[]-- (5) MISO

Bei --[]--  jeweils zum Schutz einen 220 Ohm Widerstand einbauen.

Nicht vergessen (!!!!): den AVR-Controller _direkt_  _an_  _dessen_  VCC/GND  _Pins_  (<1cm) mit 100nF abblocken.


(s. a. sep. DB25-Steckerbelegung auf: Pinbelegung_avrdude-bsd.bmp)

Achtung beim ATmega128 (und nur bei diesem!!!): 
- MISO und MOSI sind bezueglich Programmierung auf PE1 und PE0 zu finden 
  und nicht auf den mit MISO und MOSI bezeichneten Pins!!!!!!


AVRDUDE direkt aus "Programmers-Notepad" starten
Averdude kann dierekt mittels "Make Program" aus dem Programmers Notepad aufgerufen werden.
Dazu ist aber das Makefile des Projektes anzupassen.
Im Folgenden die fuer das Demo-Beispiel (C:\WinAVR\examples\demo\Makefile) noetigen Aenderungen:

# Im Deklarationsteil zu ergaenzen, z. B. fr einen ATmega8 - Controller:
#Zeile MCU_TARGET aendern auf: 

MCU_TARGET   = atmega8


#sowie darunter zufuegen von:

PGM_OPTS         = -p $(MCU_TARGET)  -c bsd  # -U lfuse:w:0xef:m   #letzteres fuer externen Clock beim ATmega8 -> s. ATmega8 Datenblatt unter Fuse Bits
AVRDUDE          = C:\WinAVR\bin\avrdude.exe

program:
	$(AVRDUDE)  $(PGM_OPTS)  -U flash:w:$(PRG).hex 



Achtung: 
- oben muss vor "$(AVRDUDE)" ein TAB-Zeichen stehen (keine Leerschlaege!)
- Fuer externen Clock beim ATmega8 ist oben das "#" vor -U zu entferenen 
- Fuer externen Clock bei anderen ATmega-Controller im Datenblatt den Abschnitt "Fusebits" konsultieren.

Funktionstest:
Als erster Funktionstest im AVR-Programmverzeichnis unter "Examples\Demo" das File "demo.c" oeffnen, 
 und mit "Tools> Make all" uebersetzen
Zum Programmieren des Chips, im Makefile obigen Teil ergaenzen, den Controller anschliessen (inkl. abgeblockte Speisung)
und "Tools> Make program" ausfuehren.

Programmieren in C:
Ein gutes Tutorial ist zu finden auf: 
 http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial


Hinweise für spezifische Chips:
- ATmega128: andere Programmierpins, s. Oben
- Bei den Chips mit mehr als 28pol. Gehäuse sind 4 Pins standardmässig durch das JTAG-Interface belegt!!!
	o Disablen softwaremässig per:  MCUCSR |= _BV(JTD);
	o oder durch löschen (=1) des programmierten (=0) Bit "JTAGEN" im "Fuse High Byte" 
	  beim ATMEGA16 (!!!) z.B per:  avrdude  ....  -u -U hfuse:w:0xd9:m 

	o falls -U auf Commandzeile nicht funktioniert, die Fusebits im avrdude Terminalmode setzen, z.B.:
	  c:\winavr\bin> avrdude -p atmega16 -c bsd -t
	  > write hfuse 0 0xd9



Nebst Datenblatt koennen koennen Fusebits auch auf folgender URL ermittelt werden:
	http://palmavr.sourceforge.net/cgi-bin/fc.cgi

Viel Spass und Erfolg, 
Matthias Meier



