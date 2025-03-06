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
- [Stima X](#stima-x)
- [Filtro bad-waveforms per gli X](#filtro-bad-waveforms-per-gli-x)
- [Acquisizioni con nuova geometria](#acquisizioni-con-nuova-geometria)

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
   $d_{detect}^{NEW}=79.1$ mm + $d_{detect}^{NEW2}=5.5$ mm
3) $h=6$ mm $850$ um ; $l=3$ mm $900$ um ; $z=1$ mm $500$ um ; $d_{targh}=16$ mm $650$ um  
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
**Calcolo del rate: (da qui in poi CAMBIO GEOMETRIA)**  
Presa dati entro ±15 gradi, come in [Test no targhetta](#test-no-targhetta), limite angolo solito.

[documentazione generale Am241](http://www.lnhb.fr/nuclides/Am-241_tables.pdf)  
[articolo Collazuol](https://www.tandfonline.com/doi/full/10.1080/00223131.2016.1174167#d1e675)
[attenuazione in foglio di carta](https://physics.nist.gov/cgi-bin/Xcom/xcom2?Method=Comp&Output2=Hand)
[attenuazione in aria](https://physics.nist.gov/PhysRefData/XrayMassCoef/ComTab/air.html)

## Filtro bad waveforms per gli X
Ci sono due principali tipologie di segnali da scartare: uno più facile da individuare, ossia sono oscillazioni di rumore senza un picco di segnale (1% all'angolo 0) (*type1*), e uno più difficile, quasi soggettivo (*type2*).  
1) filtro che elimina 100% *type1*: scartare i segnali che abbiano altezza relativa (max-min) inferiore a 2000 circa, il valore è valutato qualitativamente (pari circa al limite inferiore nell'histo dell'energia)
2) filtro che elimina 50% *type2*: dopo aver normalizzato l'integrale a 1, scartare i segnali che abbiano le seguenti caratteristiche: $x_{max}<x_0$, $y_{max}<y_0$, $int_{max}<int_0$, in questo modo si scartano i segnali che hanno il massimo eccessivamente shiftato a sinistra, l'altezza normalizzata del picco troppo bassa e l'integrale attorno al picco troppo poca (ossia significa che il resto dell'area è sparsa, magari ha la coda dx del segnale eccessivamente alta). i valori $x_0$, $y_0$, $int_0$ sono stati trovati a partire dalla media dei valori di waveform corrette
3) filtro che elimina 90% *type2*: scartare i segnali con $integral > a$, dove $integral$ è stato calcolato sui segnali rinormalizzati ponendo il massimo = 1 (si divide ogni bin/entry per il valore del massimo), e $a$ è calcolata come media dei valori dell'integrale di solo waveform corrette + 2$\times$deviazione standard
4) idea *type1/type2*: fare una media mobile del segnale (ogni valore sostituito con la media dei suoi vicini), in questo modo si eliminano i rumori ma i picchi di segnale dovrebbero rimanere nitidi. Scelta della finestra: se piccola (es.50) è utile per ridurre il rumore ad alta frequenza, se media (es.200), attenua oscillazioni casuali, se grande (es.700) evidenzia solo le strutture più ampie del segnale.




## Acquisizioni con nuova geometria
**Beam profile:**
No targhetta, test_small_angles_new, range ±15 gradi, wf pulite a 3V circa, conteggio fatto direttamente dal numero di file acquisiti e corretto poi con i valori di tempo morto trovati nei punti precedenti (non dipendendo dalla geometria dovrebbe essere corretto)

**Scattering big angles:**
Con targhetta Au, range ±47.7 gradi

## Possibili analisi aggiuntive
**Plot dell'Energy_loss delle alpha:** con coda visibile in scala logaritmica. La simulazione potrebbe spiegare l'origine delle code di alpha che vediamo e sottraiamo nella sezione sulla stima del dead time.
**Raggi X:** con i picchi visibili alle tre energie 13, 26, 60 keV è possibile ottenere una calibrazione (che vale però solo per quella sezione).
**Risoluzione in energia rispetto all'angolo**

