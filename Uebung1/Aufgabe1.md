Übung 1 - Algorithmen & Daten Strukturen 
----------------------------------------

1. Erarbeitung einer einfach verketteten Liste.

	a. Erarbeiten Sie sich die notwendige Datenstruktur einer einfach verketteten Liste.
	
		Eine einfach verkettete Liste besteht aus Knoten dennen ihr Nachfolge Knoten bekannt ist,
		die Liste ist demnach eine sequentiele Speicherung von Knoten. Die Knoten selber enthalten
		letztendlich die Nutzlast der Datenstruktur Liste. 
		
		Zur Visualisierung der Idee dient folgende Illuststation, aus dieser ist zu entnehmen, dass
		der Letzte Knoten in der Liste keinen Nachfolger besitzt. Diese Eigenschaft wird in der Implementierung 
		genutzt das Ende der Liste zu identifizieren.
		________      ________      ________
		| Data |      | Data |      | Data |
		|------|      |------|      |------|
		| Next-|----->| Next-|----->| Next-|-----> NULL
		--------      --------      --------
		
		Vorteile gegenüber einem Array:
		
		* Dynamisch weitere Knoten können jeder Zeit hinzugefügt werden
		* Einfügen und Löschen von Datensätzen ist 
			zumindestens am Anfang und am Ender der List in konstanter Zeit möglich.
		
		Nachteile gegenüber einem Array:
		
		* Ein direkte Zugriff auf ein Element ist nicht möglich,
		  für den Zugriff auf einen Knoten ist es erforderlich erst
		  über seine Vorgänger zu iterieren um auf den gewünschten Knoten
		  zu greifen zu können.
		
		
	
	b. Zu speichern in unserer Liste sind Studenten mit Vor- und Nachnamen nebst Matrikelnummer und Studiengang. Entwerfen Sie die notwendigen Datentypen und begründen Sie gegebenenfalls Ihre Wahl.  
			
	c. Implementieren Sie die notwendigen Datentypen in C unter Verwendung von typedef, struct, enum und den entsprechenden gewählten Datentypen.
		
		Siehe: Implementierung.
		
2. Funktionalität zur Verarbeitung von Elementen einer einfach verketteten Liste
	(a) Implementieren Sie eine Funktion zum Erstellen eines neuen Elements.
	(b) Implementieren Sie eine Funktion zum Hinzufügen eines Elements vor dem ersten Element.
	(c) Implementieren Sie eine Funktion zum Hinzufügen eines Elements nach dem letzten Element.
	(d) Implementieren Sie eine Funktion zur Ausgabe eines Elements der Liste.
	(e) Implementieren Sie eine Funktion zur Ausgabe der gesamten Liste.
	(f) Implementieren Sie eine Funktion zur Ausgabe der Anzahl der Elemente.
	(g) Implementieren Sie eine Funktion zum Löschen eines Elements.
	(h) Implementieren Sie eine Funktion zum Löschen der gesamten Liste.
	(i) Implementieren Sie Funktionalität zum Suchen eines oder mehrerer Studenten nach Vor- und
			Nachname, Matrikelnummer und Studiengang.
	(j) Implementieren Sie Funktionalität zum Sortieren der Datensätze der Studenten, Matrikelnummer
			und Studiengang nach zwei selbstgewählten Sortierverfahren.

3. Einige Methoden obiger einfach verketteter Liste lassen sich (im Gegensatz zum Array oder einer
	doppelt verketteten Liste) effizient (in unterschiedlicher Hinsicht) implementieren, andere
	nicht unbedingt - welche sind das und warum?

4. Implementieren Sie obige Datenstruktur und 4 der oben genannten Funktionalitäten (möglichst
laufzeiteffizienter) als doppelt verkettete Liste.

5. Analysieren Sie die Komplexität der von ihnen implementierten Sortierverfahren allgemein und
im speziellen Fall Ihrer Implementierung.
