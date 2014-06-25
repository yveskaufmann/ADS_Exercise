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

- Erstellen eines neuen Elements

Das erstellen eines Elements, welches ich an dieser Steller als das Hinzufügen eines neuen Datensatzes zur Liste interpretiere, ist im gegensatz zu einem Array in Konstanter Zeit möglich sofern alle erforderlichen Informationen bereits bekannt sind. Da der Knoten in diesem Fall nur vor bzw. hinter einem referenz Knoten eingehangen werden muss. Wenn nicht vorhanden muss dieser referenz Knoten über Iteration erst ermittelt 
werden




##4. Implementieren Sie obige Datenstruktur und 4 der oben genannten Funktionalitäten (möglichst laufzeiteffizienter) als doppelt verkettete Liste.

Da die Liste beide Varianten von vorn herein Unterstützt und deren
einziger Unterschied in der Ermittlung des Vorgänger Knoten besteht. 
Ist dies bereits implementiert wurden. 
 
Für weitere Informationen siehe die Implementierung der Liste bzw die Doxygen Kommentare. 

##5. Analysieren Sie die Komplexität der von ihnen implementierten Sortierverfahren allgemein und im speziellen Fall Ihrer Implementierung.
