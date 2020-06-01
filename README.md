# **Assignment 2 : DCT2**
* Alberici Federico - 808058
* Bettini Ivo Junior - 806878
* Cocca Umberto - 807191
* Traversa Silvia - 816435

# Introduzione
In questa relazione vengono presentate e discusse le modalità di implementazione della DCT (dall’inglese Discrete Cosine Transform), ovvero la più diffusa funzione che provvede
alla compressione spaziale.\
Nella prima parte viene confrontata la versione nativa delle DCT implementata in questo progetto con alcune varianti fast (FFT), studiandone il costo computazionale.\
Nella seconda parte viene documentato un semplice tool per applicare su immagini in toni di grigio, tramite un approccio di compressione di tipo jpeg (senza utilizzare una
matrice di quantizzazione), utilizzando tutte le funzioni DCT2 implementate, tenendo di default quella fast.

# Esecuzione del programma
Una volta avviato il programma, è possibile caricare l’immagine .bmp dal filesystem attraverso un apposito tasto e inserire i valori di F e d. Una volta inseriti i parametri,
tramite il pulsante Process viene chiamato il metodo on parameters clicked(), che dopo aver controllato se F e d rispettano tutti i vincoli (F positivo, d compreso fra 0 e 
2F - 2), trasforma con la funzione pixmapToMatrix() l’immagine in una matrice e la invia alla classe Compress.cpp. In essa l’immagine viene divisa in blocchi e a ognuno di questi
viene applicata la DCT2, restituendo poi una matrice che viene passata alla funzione matrixToPixmap() per poter essere visualizzata in output nell’interfaccia grafica.

Si rimanda alla [relazione](https://gitlab.com/AlbezJelt/dct2/-/blob/master/report/Relazione.pdf) per visualizzare l'analisi dettagliata.