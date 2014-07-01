#�bung 1 - Algorithmen & Daten Strukturen 


##1. Erarbeitung einer einfach verketteten Liste. 
 
Eine einfach verkettete Liste besteht aus Knoten dennen ihr Nachfolge Knoten bekannt ist,  
die Liste ist demnach eine sequentiele Speicherung von Knoten. Die Knoten selber enthalten  
letztendlich die Nutzlast der Datenstruktur Liste.  
Zur Visualisierung der Idee dient folgende Illuststation, aus dieser ist zu entnehmen,  
dass der Letzte Knoten in der Liste keinen Nachfolger besitzt.  
Diese Eigenschaft wird in der Implementierung genutzt das Ende der Liste zu identifizieren.
		
	________      ________      ________
	| Data |      | Data |      | Data |
	|------|      |------|      |------|
	| Next-|----->| Next-|----->| Next-|-----> NULL
	--------      --------      --------

 _Vorteile_ gegen�ber einem Array:
				
 * Eine Liste ist dynamisch, weitere Knoten k�nnen jeder Zeit hinzugef�gt werden
 * Einf�gen und L�schen von Datens�tzen ist zumindestens am Anfang   
und am Ender der List in konstanter Zeit m�glich.
		
 _Nachteile_ gegen�ber einem Array:
		
* Ein direkte Zugriff auf ein Element ist nicht m�glich,  
f�r den Zugriff auf einen Knoten ist es erforderlich erst  
�ber seine Vorg�nger zu iterieren um auf den gew�nschten Knoten  
zu greifen zu k�nnen.  
		
Entwerfen Sie die notwendigen Datentypen und begr�nden Sie gegebenenfalls Ihre Wahl.
------------------------------------------------------------------------------------ 
		 
Der geforderte Datentyp l�sst sich in 3 Datentypen aufsplitten, Liste (List),  
Knoten (Node) und Student, es wurde sich bewusst dagegen  
entschieden den Datentyp Student statisch an den Datentyp   
Knoten zu binden, da dies Ver�nderungen an der Implementierung  
bedarf sobald ein neuer Datentyp in der Liste gespeichert werden   
soll. Daher hat man sich entschieden im Datentyp Knoten einen generischen   
Zeiger f�r die Daten zu definieren, um so jeden erdenglichen Datentyp  
in der Liste speichern zu k�nnen. Dies bringt volgende Vorteile mit sich:  
		 
* Flexibilit�t der Implementierung.
* Wiederverwendbarkeit der Datentypen.
* Einfache Schnittstellen zu den Datentypen.
* Unterst�tzung f�r die Speicherung verschiedener Datentypen.
		 	
Nachteile dieses Ansatzes sind der erh�rter Speicherbedarf f�r
die erzeugten Datentypen, dies ist vernachl�ssigbar da dies
keine Anforderung dieser �bung ist.

Weiterhin ist anzumerken, dass der Datentyp List so designt bzw. implementiert
wurde, dass eine einefache und eine doppelt verkettete List �ber die
gleiche Schnittstelle (Funktionen ) zu bedienen ist. Daher muss ein Nutzer des List
Datentyps beim erstellen der Liste angeben ob er eine einfach oder eine
doppelt verkettete Liste w�nscht. Dies impleziert nat�rlich, 
dass sich List und Knoten in abh�nigkeit des gew�nschten Listen 
Typen Verhalten. 
		 	
Alle drei Datentypen abstrahieren die eigentliche Datenstruktur nach au�en hin,
durch eine Schnittstelle in Form einfacher Funktionen. Demnach ist die eigentliche
Datenstruktur au�erhalb der Implementierung ohne Benutzung dieser Funktionen
nicht m�glich. Dies hat den Vorteil bringt folgende Vorteile:
		 	
* verhindert inkonsistente Zust�nde in den Datentypen, die durch Ver�nderung  
von Au�en hevorgerufen werden k�nnten
* erm�glicht es �nderungen in der Implementierung durch zuf�hren ohne  
den Quelltext, der Gebrauch von den Datentypen macht zu �nderen.

Struktur der Datentypen
------------------------		 		  
		 		  
Der Datentyp _**Student**_ ist folgenderma�en strukturiert:

Der Vor- und Nachname sowie der Name des Studienfaches werden als `char *` pointer definiert 
um Strings beliebiger Gr��e speichern zu k�nnen.
  
Die Matrikelnummer wird als `int` gespeichert, der Preffix `s0` wird der ein�fach�heits�hal�ber nicht mit gespeichert.

	   ________________________
      | Student                |
       ------------------------    
      | char* firstName        |  
      | char* sureName         |   
      | char* courseName       |   
      | int matriculationNumber|   
      --------------------------
Der Datentyp _**Knoten**_ ist folgenderma�en strukturiert:

Der Knoten eine Liste besteht aus zwei Datentypen einen f�r
einfach verkettete Listen und einen f�r doppelt verkette Listen. Somit
kann ein wenig Speicherplatz gespart werden und das isDoupleLinkedNode
Attribute erm�glicht es der Liste zu entscheiden um welchen
Knotentypen es sich handelt. Damit die Liste den Knoten entsprechen Behandeln
kann.
                       
      __________________________       __________________________
      | NodeDoupleLinked       |       | NodeSingleLinked       |
       ------------------------         ------------------------ 
	  | bool isDoupleLinkedNode|       | bool isDoupleLinkedNode|
      | void *data        	   |       | void *data        		|  
      | Node next       	   |       | Node next       	    |  
      | Node prev			   |        ------------------------  
      --------------------------                
Der Datentyp _**List**_ ist folgenderma�en strukturiert:

Die List Datenstruktur selber dient nur als Sockel f�r die Knoten
der Liste daher speichert die Liste den ersten Knoten `root` und
den letzten Knoten `head` der Liste. Somit kann in konstanter 
Laufzeit auf den ersten bzw. den letzten Knoten zugegriffen werden.

Weiterhin wird die Anzahl `elementCount` der aktuellen Knoten in der Liste 
gespeichert, um einen Zugriff auf die Gr��e mit konstanter Laufzeit zu gew�hrleisten.

Der `destroyDataHandler` ist ein optinaler Funktions Pointer auf eine Funktion
welche die Daten eines Knoten deallokieren kann. Aufgrund des Designs der Liste
kennt diese den Datentyp der gespeicherten Daten nicht, folglich kann
diese die gespeicherten Daten selber nicht deallokieren und muss daher diese Aufgabe
an einen `destroyDataHandler` delegieren.
		 	                                    
	  ________________________________     
	  | List                          |   
	   -------------------------------    
	  | Node root                     |
	  | Node head                     |
	  | NodeHandler destroyDataHandler|
	  | size_t elementCount           |   
	  | bool isDoupleLinkedList       |
       --------------------------------

F�r mehr informationen Sie die mit DoxyGen generierte Dokumentation.
	 		
Implementieren Sie die notwendigen Datentypen in C unter Verwendung von typedef, struct, enum und den entsprechenden gew�hlten Datentypen.
----------------------------------------------------------------------------------------------------------		

Siehe die Implementierung  bzw die Doxygen Kommentare.
		
##2. Funktionalit�t zur Verarbeitung von Elementen einer einfach verketteten Liste

Siehe die Implementierung der Liste bzw die Doxygen Kommentare.
	
##3. Einige Methoden obiger einfach verketteter Liste lassen sich (im Gegensatz zum Array oder einer doppelt verketteten Liste) effizient (in unterschiedlicher Hinsicht) implementieren, andere  nicht unbedingt - welche sind das und warum?

(a) Implementieren Sie eine Funktion zum Erstellen eines neuen Elements. 

Das Erstellen eines Datensatzes (Element) ist von der Implementierung der Liste getrennt zu betrachten da, dies nicht in der Verantwortung der Liste oder des Arrays liegt.
Daher betrachte ich hier nur die Methoden zum Erstellen eines Knotens f�r eine Liste.

Die Implementierungen dieser Methode unterscheident sich nicht 
von der f�r doppelt verketteten Listen. Jediglich der erstellte Knoten
erfordert bei einer doppelt verketten Listen mehr Speicher. 

(b) Implementieren Sie eine Funktion zum Hinzuf�gen eines Elements vor dem ersten Element.  

Diese Methode l�sst sich f�r Listen generell in konstanter Zeit Implementieren,
da der neue Knoten (enth�lt das neue Element) und der erste Knoten nur �ber 
Pointer mit einander verbunden werden. 

Die Implementierung f�r ein Array der Gr��e N ist wesentlich aufw�ndiger, da 
N - 1 Verschiebungen n�tig sind um Platz f�r den neuen Datensatz zu schaffen
und das Array m�glicherweise erst mittels `realloc` Vergr��ert werden muss.

Daher l�sst sich die diese Methode f�r Listen effektiver als f�r Arrays implementieren. 
Wobei generell zu sagen ist das Arrays weniger Speicher f�r jeden Datensatz
in Anspruch nehmen.

(c) Implementieren Sie eine Funktion zum Hinzuf�gen eines Elements nach dem letzten Element. 

Diese Methode l�sst sich f�r Listen der Gr��e N generell in konstanter Zeit Implementieren,
da der neue Knoten (enth�lt das neue Element) und der letzte Knoten nur �ber 
Pointer mit einander verbunden werden. Dies setzt aber Vorraus, dass der letzte
Knoten bereits bekannt ist andernfalls muss dieser in N-1 Schritten ermittelt werden.
Um diesen Flaschenhals zu umgehen kann der letzte Knoten zwischen gespeichert werden,
dies erfordert zwar mehr Speicher und etwas mehr Aufwand bei der Implementierung um den Knoten
aktuell zuhalten, bringt aber eine konstante Laufzeit.

Die Implementierung f�r ein Array der Gr��e N erfordert die Vergr��erung
des Arrays und die damit verbundenen Verschiebe Operationen.

Damit l�sst sich diese Methode f�r Listen im Sinne der Laufzeit effektiver
implementieren. Wobei generell zu sagen ist das Arrays weniger Speicher f�r jeden Datensatz
in Anspruch nehmen.
 
(d) Implementieren Sie eine Funktion zur Ausgabe eines Elements der Liste.  

Der Aufwand f�r das Ausgaben eines Elementes h�ngt generell vom
Datensatz ab und ist unabh�nig von davon ob der Datesatz
sich in einem Array bzw in einer Liste befindet. Der eigentliche Unterschied 
zwischen der Implementierung f�r eine Array und eine Liste liegt
besteht in der Adressierung eines Datensatzes. 
Dies ist in einem Array in konstanter Zeit m�glich und daher 
l�sst sich diese Methode im Sinne der Laufzeit effektiver 
implementieren als f�r eine Liste. 

In einer Liste muss das gew�nschte Element erst durch Iterationen bzw. Suchen ermittelt werden
bevor es auf dem Bildschirm ausgeben werden kann.

Somit ist die Implementierung f�r Arrays im Sinne der Laufzeit effektiver.

(e) Implementieren Sie eine Funktion zur Ausgabe der gesamten Liste.

F�r die Ausgabe der Elemente gilt das Gleiche wie f�r Methode (d). 
Der entscheidende Faktor  ist hier die Iteration �ber alle Elemente und die entsprechende
Implementierung f�r Listen und Arrays unterscheidet sich hier nicht
gro� in der Laufzeit. Der Vorteil von Listen gegen�ber Arrays besteht darin, 
dass die Gr��e der Liste nicht bekannt sein muss, um �ber alle Elemente zu iterieren.

(f) Implementieren Sie eine Funktion zur Ausgabe der Anzahl der Elemente.

Die Ermittlung der Gr��e einer Liste erfordert das Z�hlen
von Knoten in der Liste und erfordert demnach N Operationen. 
Dieser Flaschenhals l�sst sich �hnlich wie in Methode (c) umgehen
in dem die Gr��e zwischen gespeichert wird. Was wiedrum zu einer konstanten
Laufzeit f�hrt und zu einem h�heren Speicherverbrauch pro Liste f�hrt.

In einem Array l�sst sich die Gr��e nachtr�glich nicht mehr ermitteln
und muss zwischen gespeichert werden. Somit ist die Laufzeit
wie f�r Listen ebenfalls in konstanter Zeit m�glich.

Demnach l�sst sich diese Methode "Out of the Box" f�r Arrays
effektiver implementieren. Mit der oben Beschrieben Verbesserung 
unterscheiden sich die Implementierungen f�r Listen und Arrays hinsichtlich
der Laufzeit nicht.

(g) Implementieren Sie eine Funktion zum L�schen eines Elements.  

Diese Methode l�sst sich in doppelt verketteten Listen hinsichtlich
der Laufzeit am effektivsten implementieren. Da beim L�schen eines
Elements aus der Liste der Vorg�nger des Elementes bekannt sein muss
um den Vorg�nger mit Nachfolger zu bedinden. In einfach verketteten Listen
muss der Vorg�nger erst mittels Iteration ermittelt werden
in doppelt verketteten Listen ist dies in konstanter Zeit m�glich.

Die Datens�tze eines Arrays lassen sich in konstanter Zeit l�schen
in dem der Platz des Arrays als gel�scht markiert werden. Ist die nicht m�glich muss
das Array verkleinert werden und die Elemente verschoben werden. 

(h) Implementieren Sie eine Funktion zum L�schen der gesamten Liste.  

Die Implementierungen f�r einfach und dopplet verkettete Listen
unterscheidet sich hinsichtlich der Laufzeit nicht. Da in beiden F�llen �ber
jeden Knoten iteriert werden muss um dessen Nutzlast und den Knoten 
selbst zu l�schen bzw zu deallokieren. 

Die Implementierung f�r eine Array erfordert im Grunde nur die Deallokierung
vom Array selbst. Sind im Array Datens�tze gespeichert die einer Deallokierung
bed�rfen ist zus�tzlich eine Iteration �ber das ganze Array im Vorfeld erforderlich.

Demnach l�sst sich die diese Methode f�r Arrays hinsichtlich der Laufzeit 
effektiver implementieren. 

(i) Implementieren Sie Funktionalit�t zum Suchen eines oder mehrerer Studenten nach Vor- und  
Nachname, Matrikelnummer und Studiengang.

Da Arrays im Gegensatz zu Listen einen wahlfreien Zugriff in konstanter Zeit auf die Datens�tze gew�hren, l�sst sich dies mittels bin�rer Suche effektiver f�r sortierte Arrays implementieren.
Demnach ist ein Aufwand von O(log n) n�tig. In sortieren Listen ist ein wesentlich h�herer Aufwand zu erwarten da f�r jeden Durchlauf der Binary Search die Iteration zum aktuellen Mittel Knoten erforderlich ist bzw. da Listen keinen wahlfreien Zugriff in Konstanter Zeit unterst�tzen.

(j) Implementieren Sie Funktionalit�t zum Sortieren der Datens�tze der Studenten, Matrikelnummer  
und Studiengang nach zwei selbstgew�hlten Sortierverfahren.

Generell lassen sich Sortierverfahren,welche einen direkten Zugriff auf die Elemente erfordern,
f�r Arrays effizienter hinsicht der Laufzeit implementieren im Gegensatz zu Listen. 
Da Listen im Gegensatz zu Arrays keinen Wahlfreien-Zugriff in konstanter Zeit erm�glichen. 
Ein Beispiel hierf�r ist Quick-Sort dieser "Divide and Conquer" Algorithmus
teilt die Datens�tze jeweils in zwei Teile die durch ein Piviot Element
von einander getrennt sind. Die Ermittlung dieses Piviot Element ist in
Arrays durch eine einfache Division zu ermitteln, in einer Liste muss zus�tzlich
noch �ber Knoten iteriert werden um das Piviot Element zu ermitteln. 
Im Conquer Schritt sind ebenfalls zus�tliche Iterationsschritte n�tig damit Elemente die kleiner sind als das Piviot Element in den Linken Teil des Datensatzes Verschoben werden und die die gr��eren in den rechten Teil. Somit kann man solche Algorithmen
praktisch f�r Arrays hinsichtlich der Laufzeit effizienter implementieren. 

Ein Sortierverfahren wie Mergesort unterst�tzt aber daf�r das Sortieren von Listen, welche nicht komplett in den Speicher passen, f�r solche Anwendungsf�lle eignen sich Listen erheblich besser. Da Mergesort ein "Out of place" verfahren ist
ben�tigt es f�r Arrays mehr Speicher um dieses zu sortieren. F�r Listen
existiert dieser Nachteil je nach Implementierung nicht. Somit eignet sich Mergesort f�r Listen wesentlich besser als f�r Arrays. In dieser vorliegenden Implementierung
ben�tig MergeSort etwas mehr Speicher, da im Sockel der Liste zus�tzliche Informationen gespeichert werden (anzahl der Knoten, erster/letzter Knoten).
Aber daf�r wird man mit einem theoretischen Aufwand von O(n * log(n)) belohnt.

##4. Implementieren Sie obige Datenstruktur und 4 der oben genannten Funktionalit�ten (m�glichst laufzeiteffizienter) als doppelt verkettete Liste.

Da die Liste beide Varianten von vorn herein Unterst�tzt und deren
einziger Unterschied in der Ermittlung des Vorg�nger Knoten besteht. 
Ist dies bereits implementiert worden. 
 
F�r weitere Informationen siehe die Implementierung der Liste bzw die Doxygen Kommentare. 

##5. Analysieren Sie die Komplexit�t der von ihnen implementierten Sortierverfahren allgemein und im speziellen Fall Ihrer Implementierung.

F�r die Implementierung der Sortierfunktion worde zum einen Mergesort und 
Bubblesort gew�hlt. 

