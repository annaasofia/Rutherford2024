# Advanced Physics Laboratory: Rutherford 2024

## Overview

Questo repository contiene:
- Logbook
- Codice di simulazione
- Codici di analisi
- Script da lanciare

## Accesso da remoto

Per accedere al repository da remoto, è necessario clonarlo utilizzando Git.  
Per clonare il repository, dal proprio terminale:
```bash
git clone https://github.com/tuo-username/Rutherford2024.git
```
Successivamente sarà necessario identificarsi da terminale remoto tramite:
```bash
git config user.name "username"
git config user.email "email@example.com"
```
E per lavorarci basterà semplicemente:
```bash
cd Rutherford2024
```
### Caricare le modifiche
Dopo aver fatto delle modifiche ai file nel repository locale, esegui il seguente comando per aggiungere le modifiche online:
```bash
git add .
```
Questo comando aggiunge tutti i file modificati. Se desideri aggiungere file specifici, sostituisci il punto (.) con il percorso del file. Successivamente:

```bash
git commit -m "Descrizione delle modifiche"
```
L'aggiunta di `-m "..."` serve qualora si voglia dare un titolo/commento alle modifiche. Infine, usa il comando:
```bash
git push origin main
```
Questo comando carica le modifiche nel branch principale (main). Se stai lavorando su un branch diverso, sostituisci main con il nome del branch su cui stai lavorando.  
Essendo il repository privato, assicurati di essere autenticato con il tuo account GitHub, altrimenti il push non riuscirà.

### In caso di errore
In caso di errore dopo l'inserimento della propria password dall'ultimo comando, è necessario ricorrere ad un metodo alternativo di identificazione, ossia un *personal access token (PAT)*.  
Per ottenerlo:
1. Andare su [GitHub settings](https://github.com/settings/tokens).
2. Selezionare *"Generate new token"* (classic).
3. Fornisci una descrizione (e.g., "GitHub CLI Access").
4. Sotto *"Select scopes"*, scegli il permesso (per l'accesso generico ai repository, seleziona `repo`).
5. Click *"Generate token"* in fondo.
6. Copia immediatamente il token (GitHub non te lo mostrerà più).

Ora il token potrà essere usato al posto della password quando si invia in comando `git push origin main`.

### Scaricare le modifiche
Prima di tutto, verifica di essere nella directory giusta dove hai il tuo repository Git. Puoi usare il comando:
```bash
cd /percorso/del/tuo/repository
```
Esegui il comando per ottenere le ultime modifiche dal repository remoto:
```bash
git pull origin main
```
Puoi anche usare git status per vedere se ci sono nuove modifiche scaricate nel tuo repository locale:
```bash
git status
```



