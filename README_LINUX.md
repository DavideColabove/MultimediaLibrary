# MultimediaLibrary - Guida per Linux

## Descrizione
MultimediaLibrary è un'applicazione Qt6 per la gestione di una biblioteca multimediale. Questo documento fornisce istruzioni specifiche per l'installazione e la compilazione su sistemi Linux.

## Prerequisiti

### Dipendenze di sistema
L'applicazione richiede Qt6 con i moduli base e SVG. Le dipendenze vengono installate automaticamente tramite lo script di setup.

### Distribuzioni supportate
- Ubuntu/Debian
- Fedora
- Arch Linux
- openSUSE

## Installazione rapida

### 1. Clona il repository
```bash
git clone <repository-url>
cd MultimediaLibrary
```

### 2. Esegui lo script di setup automatico
```bash
make setup
```
oppure
```bash
chmod +x scripts/setup-linux.sh
./scripts/setup-linux.sh
```

### 3. Compila ed esegui
```bash
make run
```

## Compilazione manuale

### 1. Genera il Makefile
```bash
qmake MultimediaLibrary.pro
```

### 2. Compila il progetto
```bash
make
```

### 3. Esegui l'applicazione
```bash
./build/bin/MultimediaLibrary
```

## Comandi utili

### Makefile semplificato
Il progetto include un Makefile semplificato con i seguenti target:

- `make setup` - Installa le dipendenze Qt6
- `make build` - Compila il progetto
- `make run` - Compila ed esegue l'applicazione
- `make clean` - Pulisce i file di build
- `make rebuild` - Ricompila tutto da zero
- `make help` - Mostra l'aiuto

### Compilazione parallela
Per velocizzare la compilazione, usa:
```bash
make -j$(nproc)
```

## Risoluzione problemi

### Errori di compilazione comuni

#### 1. Conversione ambigua size_t/QVariant
**Problema**: Errori di conversione tra `size_t` e `QVariant` su Linux.

**Soluzione**: Il codice è già stato corretto con `static_cast<int>(i)` per evitare ambiguità di conversione.

#### 2. Qt6 non trovato
**Problema**: `qmake: command not found` o errori di librerie Qt mancanti.

**Soluzione**: Esegui `make setup` per installare le dipendenze Qt6.

#### 3. Permessi negati
**Problema**: Errori di permessi durante l'installazione.

**Soluzione**: Assicurati di avere i privilegi sudo:
```bash
sudo make setup
```

### Verifica dell'installazione
Per verificare che tutto sia installato correttamente:
```bash
qmake --version
g++ --version
```

## Struttura del progetto
```
MultimediaLibrary/
├── src/
│   ├── Backend/          # Logica di business
│   └── Frontend/         # Interfaccia utente Qt
├── scripts/
│   └── setup-linux.sh    # Script di setup per Linux
├── samples/              # File di esempio
├── MultimediaLibrary.pro # File di progetto qmake
├── Makefile             # Makefile semplificato
└── README_LINUX.md      # Questo file
```

## Sviluppo

### Aggiungere nuove dipendenze
1. Modifica `MultimediaLibrary.pro` per aggiungere i moduli Qt necessari
2. Aggiorna `scripts/setup-linux.sh` per installare le nuove dipendenze

### Debugging
Per compilare in modalità debug:
```bash
qmake CONFIG+=debug MultimediaLibrary.pro
make
```

## Supporto
Per problemi specifici su Linux, controlla:
1. La versione di Qt installata: `qmake --version`
2. Le librerie disponibili: `ldconfig -p | grep qt6`
3. I log di compilazione per errori specifici

## Note tecniche
- Il progetto è stato testato su Ubuntu 22.04 LTS
- Utilizza Qt6 con C++17
- Supporta compilazione cross-platform (Windows/Linux)
- Include correzioni specifiche per la compatibilità Linux
