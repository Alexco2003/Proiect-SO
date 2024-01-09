# Proiect SO

# SimulareCabinet

## Cerință

 Sa se implementeze un program care simuleaza activitatea dintr-un cabinet medical: vor fi create un numar dat de thread-uri pacienti care vor astepta pentru eliberarea unor resurse reprezentand doctorii (pot fi niste structuri iar consultatia sa consiste blocarea acelei structuri si afisarea id-ului doctorului). Clientii vor ocupa resursa doctor pentru o perioada random care sa nu depaseasca o limita data. Fiecare pacient va fi generat la un interval aleator pentru o perioada data de timp. Dupa consultatie, pacientul isi va afisa timpul de asteptare si timpul consultatiei.

## Cum să rulezi

1. 
```bash
gcc -m32 proiect.c -o proiect -no-pie -pthread
```

2.
```bash
./proiect
```


