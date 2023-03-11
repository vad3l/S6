# QtyCast #
La fonction QtyCast va forcément causer des pertes car on force le cast vers un ratio qui va potentiellement donner un nombre flottant
hors nous ne pouvons pas stocker de tels nombre. (Exemple 1cm -> 1m, le ratio se transforme en 1, 0.01 n'étant pas un entier le résultat est 1cm -> 0m)

