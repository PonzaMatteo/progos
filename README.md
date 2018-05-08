# Progetto Sistemi operativi IcsScalarIpsilon: Analizzatore comandi

Esegue comandi esterni del tipo run "<cmd> <args>" gestendo le statistiche d'uso:
per ogni esecuzione tiene traccia del tempo d'esecuzione, salvando su un file di "log" le informazioni principali compreso il codice di ritorno.
Il "logger" è un processo autonomo e unico, capace di gestire la concorrenza che si può avere lanciando il tool da shell differenti anche contemporaneamente.

## Getting Started

git clone https://github.com/PonzaMatteo/progos.git

### Prerequisites

TODO

### Installing

TODO

## Running the tests

TODO

## Authors

* **Matteo Ponza**
* **Davide Ambrosi**
* **Matteo Golinelli**


See the list of [contributors](https://github.com/PonzaMatteo/progos/graphs/contributors)

struct mesg_buffer {
    long mesg_type;
    char mesg_text[MAXLEN];
    char file_name[MAXLEN];
}

 mesg_type:
  - 1 : messaggio txt se (filename == "" ) stampa ne file .txt di default
  - 2 : messaggio csv se (filename == "" ) stampa ne file .csv di default