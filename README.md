# Battaglia Navale (To Change)

#### *Segmentation Fault (core dumped)*

### 1. How to Compile:

**While you are in the main directory**

- Launch `cmake . -B <cmake-configuration-folder>`. This will create the cmake configuration folder. Note: this can't be
  named `bin`
- Run `cmake --build <cmake-configuration-folder>`. This will create a `bin` folder and will build the actual executable

At the end of the process you should be in a very similar situation

```
<Project Folder>
│   README.md
│   .gitignore
│   CMakeLists.txt    
|   statement.pdf
│
└───include
│   │   .h files
│
└───src
│   │   .cpp files
│   
└───<cmake-configuration-folder>
│   │    <cmake configuration files>
│
└───bin
│   │   <executable>
│   
```

---

### 2. Designer Notes

#### 2.1. GIT

We decided to use Git as dVCS and [GitHub](https://github.com/) as remote host. So we founded an [organization](https://github.com/UniPD-Segmentation-Fault-Core-Dumped) and created a [repository](https://github.com/UniPD-Segmentation-Fault-Core-Dumped/Prova-intermedia-di-programmazione).

In order to keep development simpler and more straightforward, we decided to use one main branch (main) and one branch per developer. For the same reason we also decided to use the following procedure:

- Pull from remote main branch.
- Switch to personal branch
- Merge/Rebase to align.
- Local development
- Add, commit
- Push to remote personal branch *(This is to have dual control and avoid a direct push to the master)*
- Pull request and merge request directly in the remote.

In this way we were able to maintain the linearity of the main branch without overlapping everyone's work.

![Network Graph](/res/NetworkGraph.png)

#### 2.2 Copy constructor

We decided not to implement the copy constructor because the default c++ copy constructor already does what it's needed


#### 2.3 Move semantics

We decided not to implement the move constructor because the default c++ move constructor already does what it's needed

---

### 3. Statement ToDo
##### Progettare e implementare la classe Book che rappresenta un libro in una biblioteca. Tale classe ha membri per contenere:
- [x] ISBN
- [x] Titolo
- [x] Nome e cognome autore (due membri diversi)
- [x] Data di copyright – la data è rappresentata usando una apposita classe Date simile a quella sviluppata a lezione;
- [x] Stato in prestito / disponibile

##### Il codice ISBN può essere rappresentata mediante una std::string oppure una classe dedicata. In ogni caso, l’ISBN deve avere il formato n-n-n-x, con n intero e x una singola cifra o una lettera (i quattro campi sono separati da un carattere ‘-’).
- [x] Done
##### La classe Book deve essere dotata di:
- [x] Funzioni membro che ritornano i vari campi
- [x] Costruttori
- [x] Funzioni per registrare il prestito e la restituzione
- [x] Appositi strumenti (eventualmente implementati nella classe dedicata) per la validazione del formato ISBN e della data
- [x] `operator==` e `operator!=` che confrontano due libri basandosi sul codice ISBN
- [x] `operator<<` che stampa titolo, autore, ISBN e la data di copyright su righe separate in output

##### La classe Book (e le altre eventuali classi) devono essere correttamente separate nei file .h e .cpp e deve essere prevista la creazione di librerie dedicate.
- [x] Done
##### Un ulteriore file .cpp deve contenere il main, usato per i test.
- [x] Done
##### È apprezzato l’utilizzo di Cmake.
- [x] Done

##### Oltre ai test necessari per lo sviluppo, devono essere compilabili le seguenti istruzioni:
- [x] `std::vector<Book> shelf(10)`;
- [x] `Book my_favourite_book(“David”, “Foster Wallace”, “Una cosa divertente
  che non farò mai più”, “887-521-837-4”)`;