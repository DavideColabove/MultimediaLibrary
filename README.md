# Multimedia Library

Una libreria multimediale completa con backend C++ e frontend Qt.

## 🚀 **Caratteristiche**

- **Backend C++**: Gestione completa di libri, film, canzoni, riviste e podcast
- **Frontend Qt**: Interfaccia grafica moderna e intuitiva
- **Sistema di Enum**: Generi e lingue tipizzati per ogni tipo di media
- **Classe Date Personalizzata**: Gestione date con validazione
- **Build System Unificato**: Makefile per backend e frontend

## 📁 **Struttura del Progetto**

```
MultimediaLibrary/
├── src/
│   ├── Backend/
│   │   ├── Elements/          # Classi base e derivate
│   │   │   ├── Media.h/.cpp   # Classe base astratta
│   │   │   ├── Book.h/.cpp    # Gestione libri
│   │   │   ├── Movie.h/.cpp   # Gestione film
│   │   │   ├── Song.h/.cpp    # Gestione canzoni
│   │   │   ├── Magazine.h/.cpp # Gestione riviste
│   │   │   ├── Podcast.h/.cpp # Gestione podcast
│   │   │   └── Date.h/.cpp    # Classe data personalizzata
│   │   ├── Enums/             # Enum per generi e lingue
│   │   │   ├── Genres.h/.cpp
│   │   │   └── Languages.h/.cpp
│   │   └── Library/           # Gestione collezione media
│   │       └── Library.h/.cpp
│   ├── Frontend/
│   │   └── Windows/
│   │       └── MainWindow.h/.cpp # Interfaccia Qt
│   └── main.cpp               # Entry point unificato
├── build/bin/                 # Eseguibili compilati
├── Makefile                   # Build system per backend
├── MultimediaLibrary.pro      # Progetto Qt
└── README.md                  # Questo file
```

## 🛠️ **Prerequisiti**

### Per il Backend (Obbligatorio)
- **MSYS2** con MinGW-w64
- **Make** (installato tramite MSYS2)
- **g++** (compilatore C++17)

### Per il Frontend Qt (Opzionale)
- **Qt 6.8.3** installato in `D:\qt\6.8.3\mingw_64`
- **Qt Creator** per sviluppo

## 🔧 **Installazione e Setup**

### 1. Installare Make (se non presente)
```bash
# Aggiungere al PATH
$env:PATH += ";C:\msys64\usr\bin"
```

### 2. Configurare Qt (se installato)
```bash
# Aggiungere Qt al PATH
$env:PATH += ";D:\qt\6.8.3\mingw_64\bin"
```

## 🏗️ **Compilazione**

### Opzione 1: Usando il Makefile Personalizzato
```bash
# Compila solo il backend test
make test

# Compila la GUI Qt (se Qt disponibile)
make gui

# Compila tutto
make all

# Pulisci i file di build
make clean

# Mostra aiuto
make help
```

### Opzione 2: Usando Qt/qmake (Raccomandato per GUI)
```bash
# Genera Makefile da progetto Qt
qmake MultimediaLibrary.pro

# Compila
make

# Pulisci
make clean
```

## 🚀 **Esecuzione**

### Modalità Test (Backend)
```bash
# Esegue test del backend in console
./build/bin/MultimediaLibraryTest
# oppure
./build/bin/MultimediaLibraryTest --test
```

### Modalità GUI
```bash
# Avvia l'interfaccia grafica Qt
./build/bin/MultimediaLibrary.exe
# oppure
./build/bin/MultimediaLibrary.exe --gui
```

### Aiuto
```bash
./build/bin/MultimediaLibraryTest --help
./build/bin/MultimediaLibrary.exe --help
```

## 📚 **Classi e Funzionalità**

### Classe Base: `Media`
- **Attributi**: title, author, releaseDate, id, kbSize, isAvailable, imagePath
- **Metodi**: getters/setters, `isValid()` (virtuale puro)

### Classi Derivate
- **`Book`**: publisher, pages, isbn, language, genre (BookGenre)
- **`Movie`**: director, duration, rating, language, genre (MovieGenre)
- **`Song`**: artist, album, duration, genre (MusicGenre)
- **`Magazine`**: publisher, issue, language, genre (MagazineGenre)
- **`Podcast`**: host, episodes, duration, genre (PodcastGenre)

### Classe `Library` (Gestione Collezione)
- **CRUD Operations**: `addMedia()`, `removeMedia()`, `findMediaById()`, `getAllMedia()`
- **Search & Filter**: `searchByTitle()`, `searchByAuthor()`, `filterByType()`, `filterByAvailability()`
- **File Operations**: `saveToFile()`, `loadFromFile()` (formato CSV)
- **Statistics**: `getTotalCount()`, `getAvailableCount()`, `getMediaTypeStats()`
- **Utility**: `getNextId()`, `clear()`, `isEmpty()`

### Sistema Enum
- **Generi**: `BookGenre`, `MovieGenre`, `MusicGenre`, `MagazineGenre`, `PodcastGenre`
- **Lingue**: `Language`
- **Conversioni**: `enumToString()`, `stringToEnum()`

## 🎨 **Interfaccia Qt**

### Componenti Principali
- **Menu Bar**: File, Edit, Search, Help
- **Tool Bar**: Azioni rapide (Add, Edit, Delete, Search, Export)
- **Table Widget**: Visualizzazione tabellare dei media
- **Status Bar**: Messaggi di stato

### Funzionalità (da implementare)
- ✅ **Struttura base** completata
- 🔄 **AddMediaDialog** - Dialog per aggiungere media
- 🔄 **EditMediaDialog** - Dialog per modificare media
- 🔄 **SearchDialog** - Dialog per cercare e filtrare
- 🔄 **Import/Export** - Salvataggio e caricamento dati

## 🔍 **Debug e Sviluppo**

### Compilazione con Debug
```bash
make debug
```

### Verifica Qt
```bash
qmake --version
```

### Verifica Make
```bash
make --version
```

## 📝 **Note di Sviluppo**

### Per Aprire in Qt Creator
1. Apri `MultimediaLibrary.pro` in Qt Creator
2. Configura il kit MinGW
3. Compila ed esegui direttamente da Qt Creator

### Per Sviluppo da Terminale
1. Usa `make test` per testare il backend
2. Usa `qmake && make` per compilare la GUI
3. Usa `./build/bin/MultimediaLibrary.exe` per eseguire

## 🎯 **Prossimi Passi**

1. **Implementare AddMediaDialog** con ComboBox per generi e lingue
2. **Implementare EditMediaDialog** per modificare media esistenti
3. **Implementare SearchDialog** per cercare e filtrare
4. **Aggiungere validazione input** con QValidator
5. **Implementare salvataggio/caricamento** dati
6. **Aggiungere stili CSS** per migliorare l'aspetto

## ✅ **Stato Attuale**

- ✅ **Backend**: Completamente funzionante
- ✅ **Classi derivate**: Implementate con enum
- ✅ **Classe Library**: Gestione completa della collezione
- ✅ **Sistema build**: Makefile e qmake funzionanti
- ✅ **GUI base**: MainWindow con menu e toolbar
- ✅ **Qt integration**: Compilazione e linking corretti
- 🔄 **Dialog**: In sviluppo
- 🔄 **Funzionalità avanzate**: Da implementare

---

**Sviluppato con C++17, Qt 6.8.3 e Make** 🚀
