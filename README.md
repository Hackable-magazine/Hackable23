Sources et fichiers pour le magazine Hackable #23
=================================================

Ce dépôt contient les croquis, sources et fichiers utilisés dans le 23ème numéro de [Hackable](http://www.hackable.fr/) :

* `gsmloop` : croquis Arduino permettant le dialogue interactif avec le module/shield GSM/SIM900 à l'aide de commandes Hayes (AT).
* `GPRSenvoiSMS` : croquis Arduino du moniteur de température avec message de service quotidien et alertes SMS en cas de dépassement de consigne.
* `GPRSnet` : croquis Arduino de test de la connexion GPRS (non traité dans le magazine).
* `esp32multiok` : croquis Arduino de démonstration des fonctionnalités multitâches de l'ESP32.
* `Z80ctl_memRAM` : croquis Arduino du "moniteur" Z80 avec émulation de RAM (lecture et écriture en mémoire).
* `Z80ctl_mem_74165RAM` : Idem mais en utilisant deux 74HCT165 pour lire l'ensemble les 16 bits d'adresse du bus (davantage de mémoire émulée).
* `sdcc_test` : source C (+ runtime assembleur) et script de compilation pour le montage Z80.

