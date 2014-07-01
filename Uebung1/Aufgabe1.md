#Übung 1 - Algorithmen & Daten Strukturen 


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

 _Vorteile_ gegenüber einem Array:
				
 * Eine Liste ist dynamisch, weitere Knoten können jeder Zeit hinzugefügt werden
 * Einfügen und Löschen von Datensätzen ist zumindestens am Anfang   
und am Ender der List in konstanter Zeit möglich.
		
 _Nachteile_ gegenüber einem Array:
		
* Ein direkte Zugriff auf ein Element ist nicht möglich,  
für den Zugriff auf einen Knoten ist es erforderlich erst  
über seine Vorgänger zu iterieren um auf den gewünschten Knoten  
zu greifen zu können.  
		
Entwerfen Sie die notwendigen Datentypen und begründen Sie gegebenenfalls Ihre Wahl.
------------------------------------------------------------------------------------ 
		 
Der geforderte Datentyp lässt sich in 3 Datentypen aufsplitten, Liste (List),  
Knoten (Node) und Student, es wurde sich bewusst dagegen  
entschieden den Datentyp Student statisch an den Datentyp   
Knoten zu binden, da dies Veränderungen an der Implementierung  
bedarf sobald ein neuer Datentyp in der Liste gespeichert werden   
soll. Daher hat man sich entschieden im Datentyp Knoten einen generischen   
Zeiger für die Daten zu definieren, um so jeden erdenglichen Datentyp  
in der Liste speichern zu können. Dies bringt volgende Vorteile mit sich:  
		 
* Flexibilität der Implementierung.
* Wiederverwendbarkeit der Datentypen.
* Einfache Schnittstellen zu den Datentypen.
* Unterstützung für die Speicherung verschiedener Datentypen.
		 	
Nachteile dieses Ansatzes sind der erhörter Speicherbedarf für
die erzeugten Datentypen, dies ist vernachlässigbar da dies
keine Anforderung dieser Übung ist.

Weiterhin ist anzumerken, dass der Datentyp List so designt bzw. implementiert
wurde, dass eine einefache und eine doppelt verkettete List über die
gleiche Schnittstelle (Funktionen ) zu bedienen ist. Daher muss ein Nutzer des List
Datentyps beim erstellen der Liste angeben ob er eine einfach oder eine
doppelt verkettete Liste wünscht. Dies impleziert natürlich, 
dass sich List und Knoten in abhänigkeit des gewünschten Listen 
Typen Verhalten. 
		 	
Alle drei Datentypen abstrahieren die eigentliche Datenstruktur nach außen hin,
durch eine Schnittstelle in Form einfacher Funktionen. Demnach ist die eigentliche
Datenstruktur außerhalb der Implementierung ohne Benutzung dieser Funktionen
nicht möglich. Dies hat den Vorteil bringt folgende Vorteile:
		 	
* verhindert inkonsistente Zustände in den Datentypen, die durch Veränderung  
von Außen hevorgerufen werden könnten
* ermöglicht es Änderungen in der Implementierung durch zuführen ohne  
den Quelltext, der Gebrauch von den Datentypen macht zu änderen.

Struktur der Datentypen
------------------------		 		  
		 		  
Der Datentyp _**Student**_ ist folgendermaßen strukturiert:

Der Vor- und Nachname sowie der Name des Studienfaches werden als `char *` pointer definiert 
um Strings beliebiger Größe speichern zu können.
  
Die Matrikelnummer wird als `int` gespeichert, der Preffix `s0` wird der ein­fach­heits­hal­ber nicht mit gespeichert.

	   ________________________
      | Student                |
       ------------------------    
      | char* firstName        |  
      | char* sureName         |   
      | char* courseName       |   
      | int matriculationNumber|   
      --------------------------
Der Datentyp _**Knoten**_ ist folgendermaßen strukturiert:

Der Knoten eine Liste besteht aus zwei Datentypen einen für
einfach verkettete Listen und einen für doppelt verkette Listen. Somit
kann ein wenig Speicherplatz gespart werden und das isDoupleLinkedNode
Attribute ermöglicht es der Liste zu entscheiden um welchen
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
Der Datentyp _**List**_ ist folgendermaßen strukturiert:

Die List Datenstruktur selber dient nur als Sockel für die Knoten
der Liste daher speichert die Liste den ersten Knoten `root` und
den letzten Knoten `head` der Liste. Somit kann in konstanter 
Laufzeit auf den ersten bzw. den letzten Knoten zugegriffen werden.

Weiterhin wird die Anzahl `elementCount` der aktuellen Knoten in der Liste 
gespeichert, um einen Zugriff auf die Größe mit konstanter Laufzeit zu gewährleisten.

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

Für mehr informationen Sie die mit DoxyGen generierte Dokumentation.
	 		
Implementieren Sie die notwendigen Datentypen in C unter Verwendung von typedef, struct, enum und den entsprechenden gewählten Datentypen.
----------------------------------------------------------------------------------------------------------		

Siehe die Implementierung  bzw die Doxygen Kommentare.
		
##2. Funktionalität zur Verarbeitung von Elementen einer einfach verketteten Liste

Siehe die Implementierung der Liste bzw die Doxygen Kommentare.
	
##3. Einige Methoden obiger einfach verketteter Liste lassen sich (im Gegensatz zum Array oder einer doppelt verketteten Liste) effizient (in unterschiedlicher Hinsicht) implementieren, andere  nicht unbedingt - welche sind das und warum?

(a) Implementieren Sie eine Funktion zum Erstellen eines neuen Elements. 

Das Erstellen eines Datensatzes (Element) ist von der Implementierung der Liste getrennt zu betrachten da, dies nicht in der Verantwortung der Liste oder des Arrays liegt.
Daher betrachte ich hier nur die Methoden zum Erstellen eines Knotens für eine Liste.

Die Implementierungen dieser Methode unterscheident sich nicht 
von der für doppelt verketteten Listen. Jediglich der erstellte Knoten
erfordert bei einer doppelt verketten Listen mehr Speicher. 

(b) Implementieren Sie eine Funktion zum Hinzufügen eines Elements vor dem ersten Element.  

Diese Methode lässt sich für Listen generell in konstanter Zeit Implementieren,
da der neue Knoten (enthält das neue Element) und der erste Knoten nur über 
Pointer mit einander verbunden werden. 

Die Implementierung für ein Array der Größe N ist wesentlich aufwändiger, da 
N - 1 Verschiebungen nötig sind um Platz für den neuen Datensatz zu schaffen
und das Array möglicherweise erst mittels `realloc` Vergrößert werden muss.

Daher lässt sich die diese Methode für Listen effektiver als für Arrays implementieren. 
Wobei generell zu sagen ist das Arrays weniger Speicher für jeden Datensatz
in Anspruch nehmen.

(c) Implementieren Sie eine Funktion zum Hinzufügen eines Elements nach dem letzten Element. 

Diese Methode lässt sich für Listen der Größe N generell in konstanter Zeit Implementieren,
da der neue Knoten (enthält das neue Element) und der letzte Knoten nur über 
Pointer mit einander verbunden werden. Dies setzt aber Vorraus, dass der letzte
Knoten bereits bekannt ist andernfalls muss dieser in N-1 Schritten ermittelt werden.
Um diesen Flaschenhals zu umgehen kann der letzte Knoten zwischen gespeichert werden,
dies erfordert zwar mehr Speicher und etwas mehr Aufwand bei der Implementierung um den Knoten
aktuell zuhalten, bringt aber eine konstante Laufzeit.

Die Implementierung für ein Array der Größe N erfordert die Vergrößerung
des Arrays und die damit verbundenen Verschiebe Operationen.

Damit lässt sich diese Methode für Listen im Sinne der Laufzeit effektiver
implementieren. Wobei generell zu sagen ist das Arrays weniger Speicher für jeden Datensatz
in Anspruch nehmen.
 
(d) Implementieren Sie eine Funktion zur Ausgabe eines Elements der Liste.  

Der Aufwand für das Ausgaben eines Elementes hängt generell vom
Datensatz ab und ist unabhänig von davon ob der Datesatz
sich in einem Array bzw in einer Liste befindet. Der eigentliche Unterschied 
zwischen der Implementierung für eine Array und eine Liste liegt
besteht in der Adressierung eines Datensatzes. 
Dies ist in einem Array in konstanter Zeit möglich und daher 
lässt sich diese Methode im Sinne der Laufzeit effektiver 
implementieren als für eine Liste. 

In einer Liste muss das gewünschte Element erst durch Iterationen bzw. Suchen ermittelt werden
bevor es auf dem Bildschirm ausgeben werden kann.

Somit ist die Implementierung für Arrays im Sinne der Laufzeit effektiver.

(e) Implementieren Sie eine Funktion zur Ausgabe der gesamten Liste.

Für die Ausgabe der Elemente gilt das Gleiche wie für Methode (d). 
Der entscheidende Faktor  ist hier die Iteration über alle Elemente und die entsprechende
Implementierung für Listen und Arrays unterscheidet sich hier nicht
groß in der Laufzeit. Der Vorteil von Listen gegenüber Arrays besteht darin, 
dass die Größe der Liste nicht bekannt sein muss, um über alle Elemente zu iterieren.

(f) Implementieren Sie eine Funktion zur Ausgabe der Anzahl der Elemente.

Die Ermittlung der Größe einer Liste erfordert das Zählen
von Knoten in der Liste und erfordert demnach N Operationen. 
Dieser Flaschenhals lässt sich ähnlich wie in Methode (c) umgehen
in dem die Größe zwischen gespeichert wird. Was wiedrum zu einer konstanten
Laufzeit führt und zu einem höheren Speicherverbrauch pro Liste führt.

In einem Array lässt sich die Größe nachträglich nicht mehr ermitteln
und muss zwischen gespeichert werden. Somit ist die Laufzeit
wie für Listen ebenfalls in konstanter Zeit möglich.

Demnach lässt sich diese Methode "Out of the Box" für Arrays
effektiver implementieren. Mit der oben Beschrieben Verbesserung 
unterscheiden sich die Implementierungen für Listen und Arrays hinsichtlich
der Laufzeit nicht.

(g) Implementieren Sie eine Funktion zum Löschen eines Elements.  

Diese Methode lässt sich in doppelt verketteten Listen hinsichtlich
der Laufzeit am effektivsten implementieren. Da beim Löschen eines
Elements aus der Liste der Vorgänger des Elementes bekannt sein muss
um den Vorgänger mit Nachfolger zu bedinden. In einfach verketteten Listen
muss der Vorgänger erst mittels Iteration ermittelt werden
in doppelt verketteten Listen ist dies in konstanter Zeit möglich.

Die Datensätze eines Arrays lassen sich in konstanter Zeit löschen
in dem der Platz des Arrays als gelöscht markiert werden. Ist die nicht möglich muss
das Array verkleinert werden und die Elemente verschoben werden. 

(h) Implementieren Sie eine Funktion zum Löschen der gesamten Liste.  

Die Implementierungen für einfach und dopplet verkettete Listen
unterscheidet sich hinsichtlich der Laufzeit nicht. Da in beiden Fällen über
jeden Knoten iteriert werden muss um dessen Nutzlast und den Knoten 
selbst zu löschen bzw zu deallokieren. 

Die Implementierung für eine Array erfordert im Grunde nur die Deallokierung
vom Array selbst. Sind im Array Datensätze gespeichert die einer Deallokierung
bedürfen ist zusätzlich eine Iteration über das ganze Array im Vorfeld erforderlich.

Demnach lässt sich die diese Methode für Arrays hinsichtlich der Laufzeit 
effektiver implementieren. 

(i) Implementieren Sie Funktionalität zum Suchen eines oder mehrerer Studenten nach Vor- und  
Nachname, Matrikelnummer und Studiengang.

Da Arrays im Gegensatz zu Listen einen wahlfreien Zugriff in konstanter Zeit auf die Datensätze gewähren, lässt sich dies mittels binärer Suche effektiver für sortierte Arrays implementieren.
Demnach ist ein Aufwand von O(log n) nötig. In sortieren Listen ist ein wesentlich höherer Aufwand zu erwarten da für jeden Durchlauf der Binary Search die Iteration zum aktuellen Mittel Knoten erforderlich ist bzw. da Listen keinen wahlfreien Zugriff in Konstanter Zeit unterstützen.

(j) Implementieren Sie Funktionalität zum Sortieren der Datensätze der Studenten, Matrikelnummer  
und Studiengang nach zwei selbstgewählten Sortierverfahren.

Generell lassen sich Sortierverfahren,welche einen direkten Zugriff auf die Elemente erfordern,
für Arrays effizienter hinsicht der Laufzeit implementieren im Gegensatz zu Listen. 
Da Listen im Gegensatz zu Arrays keinen Wahlfreien-Zugriff in konstanter Zeit ermöglichen. 
Ein Beispiel hierfür ist Quick-Sort dieser "Divide and Conquer" Algorithmus
teilt die Datensätze jeweils in zwei Teile die durch ein Piviot Element
von einander getrennt sind. Die Ermittlung dieses Piviot Element ist in
Arrays durch eine einfache Division zu ermitteln, in einer Liste muss zusätzlich
noch über Knoten iteriert werden um das Piviot Element zu ermitteln. 
Im Conquer Schritt sind ebenfalls zusätliche Iterationsschritte nötig damit Elemente die kleiner sind als das Piviot Element in den Linken Teil des Datensatzes Verschoben werden und die die größeren in den rechten Teil. Somit kann man solche Algorithmen
praktisch für Arrays hinsichtlich der Laufzeit effizienter implementieren. 

Ein Sortierverfahren wie Mergesort unterstützt aber dafür das Sortieren von Listen, welche nicht komplett in den Speicher passen, für solche Anwendungsfälle eignen sich Listen erheblich besser. Da Mergesort ein "Out of place" verfahren ist
benötigt es für Arrays mehr Speicher um dieses zu sortieren. Für Listen
existiert dieser Nachteil je nach Implementierung nicht. Somit eignet sich Mergesort für Listen wesentlich besser als für Arrays. In dieser vorliegenden Implementierung
benötig MergeSort etwas mehr Speicher, da im Sockel der Liste zusätzliche Informationen gespeichert werden (anzahl der Knoten, erster/letzter Knoten).
Aber dafür wird man mit einem theoretischen Aufwand von O(n * log(n)) belohnt.

##4. Implementieren Sie obige Datenstruktur und 4 der oben genannten Funktionalitäten (möglichst laufzeiteffizienter) als doppelt verkettete Liste.

Da die Liste beide Varianten von vorn herein Unterstützt und deren
einziger Unterschied in der Ermittlung des Vorgänger Knoten besteht. 
Ist dies bereits implementiert worden. 
 
Für weitere Informationen siehe die Implementierung der Liste bzw die Doxygen Kommentare. 

##5. Analysieren Sie die Komplexität der von ihnen implementierten Sortierverfahren allgemein und im speziellen Fall Ihrer Implementierung.

Für die Implementierung der Sortierfunktion worde zum einen Mergesort und 
Bubblesort gewählt. 

