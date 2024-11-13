# RUTHERFORD 2024

**Participants**: Arianna Pajola, Anna Sofia Moro, Vito Troia

## Indice
- [Accesso da remoto](#accesso-da-remoto)
- [Acquisizione](#acquisizione)
- [Dimensioni setup](#dimensioni-setup)
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

## Acquisizione
```bash
cd Scrivania/RuShield_Control/v3/main/main
```
```bash
./main
./main ../../../../Rutherford_2024/script.script
```
dove `./main` apre solo l'interfaccia di Rushield, da cui si può avviare il motore e calibrare manualmente.

**Center:** $\phi_0=145.8°=162$ steps

## Dimensioni setup
Misure effettuate con calibro, che ha precisione di $\pm0.05$ mm  
**Collimatori:**  
1) $h=6$ mm $850$ um ; $l=3$ mm $850$ um ; $z=1$ mm $500$ um ; $d_{targh}=0.9$ mm ; $d_{detect}=78.1$ mm
2) $h=6$ mm $850$ um ; $l=3$ mm $900$ um ; $z=1$ mm $500$ um ; $d_{targh}=16$ mm $650$ um  
dove con $d_{targh}$ si intendono le distanze dei collimatori dalla targhetta, spessori esclusi, e con $d_{detect}$ distanza collimatore-detector.

collimatore del SiPM $h=3.4$ mm ; $l=3.5$ mm

**Sorgente:**  
diametro $d_S=7.5$ mm

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
$\tau_D=(1-\frac{N_{osserv}}{N_{attese}})$ in percentuale   
dove $N_{oss}$ numero di waveforms osservate a partire dai dati, $N_{att}$ sono le waveforms attese calcolate come $floor(t_{run}/\tau)$, dove $t_{run}$ è il runtime totale (impostato+exceeded) e $\tau$ è il periodo impostato nel pulser (1s o 10s).

Per correggere i dati:  
$N_{true}=\frac{N}{(1-\tau_D)}$

**Analisi di $N_{osservate}$:**
- [read_waveforms2.cpp](./scripts/read_waveforms2.cpp)
- integrazione entro 3 sigma attorno al picco $\to$ non sempre efficiente
- integrazione entro 3 sigma dopo una sottrazione di un fondo/coda delle alfa $\to$ risulta sempre $N_{oss}<N_{att}$
- *attenzione: se possibile preferire un ciclo* `for` *sugli eventi con* `if` *statements per filtrare gli eventi piuttosto che la funzione* `->Integral(min,max)` *che usa il numero di bin, perdendo così di notevole precisione*


## Stima X
Targhetta di carta con grammatura ∼100 g/mq.  
Presa dati circa centrato sullo zero (problemi motorino) con **gain 1k** e con diversi valori di trigger: 150mV, 200mV, 250 mV ([X_center.script](./scripts/X_center.script))    
**Calcolo del rate:**  
Presa dati entro ±15 gradi, come in [Test no targhetta](#test-no-targhetta), limite angolo solito.

[documentazione generale Am241](http://www.lnhb.fr/nuclides/Am-241_tables.pdf)  
[articolo Collazuol](https://www.tandfonline.com/doi/full/10.1080/00223131.2016.1174167#d1e675)



