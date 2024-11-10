# RUTHERFORD 2024

**Participants**: Arianna Pajola, Anna Sofia Moro, Vito Troia

## Indice
- [Accesso da remoto](#accesso-da-remoto)
- [Simulazione](#simulazione)
- [Test no targhetta](#test-no-targhetta)
- [Targhetta Au: piccoli angoli](#targhetta-au-piccoli-angoli)
- [Pulser: stima del dead time](#pulser-stima-del-dead-time)

## Accesso da remoto
Per trovare l'IP del computer:
```bash
curl ifconfig.me
```
ottenendo `147.162.55.95`. E quindi per accedere:
```bash
ssh -XY collazuo@147.162.55.95
```
con password: `rat0r90`.

Per invece copiare files, dal proprio terminale lanciare il comando:
```bash
scp collazuo@147.162.55.95:Scrivania/Rutherford_2024/your/path .
```
dove il `.` significa *here*, altrimenti indicare il percorso tramite `./your/path/here`.

## Simulazione
**Codes:** [Newsim7.cpp](./codes/Newsim7.cpp)
Sorgente non puntiforme, energia alpha emesse 4.7 MeV, un collimatore.
**Beam profile:** traiettorie rettilinee, condizione di passaggio per il collimatore e di arrivo nel detector.
**Scattering profile:** come sopra ma con scattering; in targhetta step minore del cammino libero medio, se si verifica lo scattering generazione del parametro d'impatto (range di b fissato da confronto tra angular straggling su Lise++ e distribuzione angolare finale), cambio direzione dopo lo scattering, ripeti fino all'uscita dalla targhetta.
Lo spessore della targhetta è stato variato per ottenere delle code più simili ai dati, come valore finale è stato assunto 0.16 um

## Test no targhetta

## Targhetta Au: piccoli angoli
**Script:** [Au_small_angles.script](./scripts/Au_small_angles.script) da -22.5 a +25.2 gradi.

## Pulser: stima del dead time

## Stima X
Targhetta di carta con grammatura ∼100 g/mq.  
**Calcolo del rate:**  
Presa dati entro ±15 gradi, come in [Test no targhetta](#test-no-targhetta), limite angolo solito. E, tenendo conto che sono probabilmente dati da transizioni, ...  

[documentazione generale Am241](http://www.lnhb.fr/nuclides/Am-241_tables.pdf)



