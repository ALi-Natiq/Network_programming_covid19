# Network_programming_covid19
Deze service geeft geografische distributie van COVID-19 wereldwijd voor de periode van 1/1/2020 t.e.m 14/12/2020.                 
De gebruiker kan gewoon de student.cpp applicatie gebruiken om van de service te genieten.
Als de gebruiker het programma student runt, wordt hij gevraagd om een paar gegevens in te geven bv. land ,comando , datum.       
Service gaat (afhankelijk van de comando van de gebruiker) doden , besmettingen , continent van het land ezv. terug sturen.


![np](https://user-images.githubusercontent.com/46653906/120383593-5c9e0c00-c325-11eb-95d8-3a320aed6ed7.png)

Het programma server.py zorgt dat als benternet server niet werkt , dan kan je server.py runnen op je rspberry pi en die gaat werken als proxy server.    
In dit geval moet je natuurlijk deze 2 lijnen aanpassen:                                                                                    
sub->connectTo("tcp://benternet.pxl-ea-ict.be:24042"); naar je eigen ip met een poort bv. "tcp://192.168.1.1:5554"                       
send->connectTo("tcp://benternet.pxl-ea-ict.be:24041"); naar je eigen ip met een poort bv. "tcp://192.168.1.1:5555"                                
In student programma als in covid_service programma.
