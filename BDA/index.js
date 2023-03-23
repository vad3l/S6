// express
const express = require('express');
const bodyParser= require('body-parser');
const app = express();

app.use(express.static('public'));

app.listen(8080, function() {
  console.log('En attente de connexions sur le port 8080')
});

app.use(bodyParser.json())

/*** Ouvrir la connexion à MongoDB ici ***/


/*** Routes existantes **/
app.post("/messages/:date", function(req, res) {
    console.log("Reçu : POST /messages/" + req.params.date + " de " + req.body.login);
    // cf. Etape 6 de la séance 1.
});


app.put("/message", function(req, res) {
    console.log("Reçu : PUT /message de " + req.body.login +
                "\n - Destinataire : " + req.body.to.join(", ") +
                "\n - Sujet : " + req.body.subject);
    // cf. Etape 6 de la séance 1.
});
