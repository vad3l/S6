"use strict";

document.addEventListener("DOMContentLoaded", function() {
    
    /** Objet sockant les messages de la boite de réception */
    var inbox = {};
        
    /** Date de la dernière mise à jour au format AAAAMMJJHHMMSS */
    var lastUpdate = 0;
    
    /**
     * Clic sur le bouton "Recevoir" 
     *   --> envoi de la requête POST au serveur
     *   --> sauvegarde des messages dans l'objet "inbox"
     *   --> affichage du résultat (nouveaux messages insérés dans le tableau pour l'affichage)
     */
    document.getElementById("btnRecevoir").addEventListener("click", function(_e) {
        // verification login/mdp non vide
        var login = document.getElementById("txtLogin").value.trim();
        var password = document.getElementById("txtPasse").value.trim();
        if (login.length == 0 || password.length == 0) {
            alert("Login/mot de passe vides. Merci de remplir ces paramètres.");
            return;
        }
        // récupération des messages en envoyant une requete POST avec les login/mdp et la date de dernière récupération 
        fetch("/messages/" + lastUpdate, {
            method: 'post',
            headers: {
                'Accept': 'application/json',
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ login: login, password: password })
        }).then(function(response) {
            return response.json();
        }).then(function(data) {
            // affichage messages reçus 
            if (data) {
                var table = document.querySelector("section table tbody");
                data.reverse().forEach(function(e) {
                    if (!inbox[e._id]) {
                        inbox[e._id] = e;
                        var tr = document.createElement("tr");
                        tr.dataset.msg = e._id;
                        tr.innerHTML = "<td>" + e.from + "</td><td>" + e.subject + "</td><td>" + strToDate(e.date) + "</td>";
                        table.insertBefore(tr, table.firstChild);
                    }
                });
                lastUpdate = dateToStr(new Date());
            }
            else {
                alert("Erreur dans l'identification. ");   
            }
        });
        
    });
    
    
    /** 
     *  Clic sur un des messages affichés 
     *      --> affichage du message complet dans la zone prévue à cet effet.
     */
    document.querySelector("section table tbody").addEventListener("click", function(e) {
        var target = e.target;
        if (target.tagName == "TD") {
            target = target.parentElement;   
        }
        if (! target.dataset.msg) {
            return;   
        }
        // ajout de l'ID est dans l'attribut data-msg du <tr>
        var id = target.dataset.msg;
        // affichage dans le bloc <article>
        var article = document.querySelector("article");
        article.querySelector(".from").innerHTML = inbox[id].from;
        article.querySelector(".to").innerHTML = inbox[id].to.join(", ");
        article.querySelector(".subject").innerHTML = inbox[id].subject;
        article.querySelector(".date").innerHTML = strToDate(inbox[id].date);
        article.querySelector("div").innerHTML = "<p>" + inbox[id].content.replace(/\n\n/g, "</p><p>").replace(/\n/g,"<br>") + "</p>";
        article.dataset.msg = id;
    });
    
    
    /** Clic sur le bouton rédiger **/
    document.getElementById("btnRediger").addEventListener("click", function(e) {
        rediger("","",""); 
    });

    /** Clic sur les boutons Répondre, Répondre à tous, Transférer, Supprimer **/
    document.getElementById("btnReply").addEventListener("click", function(e) {
        var msg = inbox[document.querySelector("article[data-msg]").dataset.msg];
        rediger(msg.from, 
                "Re: " + msg.subject, 
                "\n\n---\nMessage répondu, reçu le " + strToDate(msg.date) + "\nDe : " + msg.from + "\nPour : " + msg.to.join(", ")+"\n\n" + msg.content
               );
    });
    document.getElementById("btnReplyAll").addEventListener("click", function(e) {
        var msg = inbox[document.querySelector("article[data-msg]").dataset.msg];
        rediger([msg.from].concat(msg.to), 
                "Re: " + msg.subject, 
                "\n\n---\nMessage répondu, reçu le " + strToDate(msg.date) + "\nDe : " + msg.from + "\nPour : " + msg.to.join(", ")+"\n\n" + msg.content
               );
    });
    document.getElementById("btnForward").addEventListener("click", function(e) {
        var msg = inbox[document.querySelector("article[data-msg]").dataset.msg];
        rediger("", 
                "Fw: " + msg.subject, 
                "\n\n---\nMessage transféré, reçu le " + strToDate(msg.date) + "\nDe : " + msg.from + "\nPour : " + msg.to.join(", ")+"\n\n" + msg.content
               );
    });
    document.getElementById("btnDelete").addEventListener("click", function(e) {
        alert("TODO séance TP2");   
    });
    
    /** Clic sur les boutons de l'interface de rédaction de mail */
    document.getElementById("btnCloseNew").addEventListener("click", function(e) {
        if (confirm("Voulez-vous quitter le mail en cours de rédaction ?")) {
            this.parentElement.classList.remove("show");
        }
    });
    
    
    /** 
     *  Clic sur le bouton d'envoi du message 
     *      --> vérification des 
     */
    document.getElementById("btnSendMessage").addEventListener("click", function(e) {
        // verification login/mdp non vide
        var login = document.getElementById("txtLogin").value.trim();
        var password = document.getElementById("txtPasse").value.trim();
        if (login.length == 0 || password.length == 0) {
            alert("Login/mot de passe vides. Merci de remplir ces paramètres.");
            return;
        }
        // vérification destinataires non vides
        var dest = document.getElementById("txtTo").value.split(" ").map(e => e.trim()).filter(e => e.length > 0);
        if (dest.length == 0) {
            alert("La liste des destinataires est vide.");
            return;
        }
        // vérification sujet non vide
        var sujet = document.getElementById("txtSubject").value.trim();
        if (sujet.length == 0 && !confirm("Le sujet du message est vide. Envoyer quand même ?")) {
            return;   
        }
        // vérification contenu du message non vide
        var contenu = document.getElementById("txtContent").value.trim();
        if (contenu.length == 0 && !confirm("Le contenu du message est vide. Envoyer quand même ?")) {
            return;   
        }
        // confirmation d'envoi
        if (!confirm("Voulez-vous envoyer ce message maintenant ?")) {
            return;
        }
        // envoi du message PUT au serveur
        fetch("/message", {
            method: 'put',
            headers: {
                'Accept': 'application/json',
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ 
                login: login, 
                password: password, 
                to: dest, 
                subject: sujet, 
                content: contenu 
            })
        }).then(function(res) {
            return res.json();
        }).then(function(json) {
            if (!json) {
                alert("Erreur dans l'identification. ");   
            }
            else {
                if (json.count >= 0) {
                    alert("Message envoyé à " + json.count + " destinataire(s)");
                }
                document.querySelector("main").classList.remove("show");
            }
        });
    });
    
    
    /** Clic sur le bouton boite de réception **/
    document.getElementById("btnInbox").addEventListener("click", function(e) {
        alert("TODO séance TP2")
    });
    
    /** Clic sur le bouton messages envoyés **/
    document.getElementById("btnSent").addEventListener("click", function(e) {
        alert("TODO séance TP2")
    });
    
    /** Clic sur le bouton messages supprimés **/
    document.getElementById("btnTrash").addEventListener("click", function(e) {
        alert("TODO séance TP2")
    });
    

    
    /**
     *  Ouvre la fenêtre de rédaction d'un message avec les éléments pré-remplis.
     */
    function rediger(to, subject, content) {
        var main = document.querySelector("main");
        if (!main.classList.contains("show") || confirm("Abandonner le mail en cours de rédaction ?")) {
            document.getElementById("txtTo").value = to.join ? to.join(" ") : to;
            document.getElementById("txtSubject").value = subject;
            document.getElementById("txtContent").value = content;
            document.getElementById("txtContent").focus();
            main.classList.add("show");
        }
    }
    
    
    
    /************************************************** 
     *      Fonctions utilitaires sur les dates 
     ***************************************************/
    
    /** Affichage "propre" d'un chaine AAAAMMJJHHMMSS au format JJ/MM/AAAAA à HH:MM:SS **/
    function strToDate(str) {
        str = String(str);
        var annee = str.substr(0, 4);   
        var mois = str.substr(4, 2);   
        var jour = str.substr(6, 2);   
        var hh = str.substr(8, 2);   
        var mm = str.substr(10, 2);   
        var ss = str.substr(12, 2);   
        return `${Number(jour)}/${mois}/${annee} à ${hh}:${mm}:${ss}`;
    }
    
    /** Création d'une chaine AAAAMMJJHHMMSS à partir d'un objet Date donné **/
    function dateToStr(now) {
        return "" + now.getFullYear()                       // année sur 4 chiffres
                  + ("0" + (now.getMonth()+1)).slice(-2)    // mois sur 2 chiffres
                  + ("0" + now.getDate()).slice(-2)         // jour ...
                  + ("0" + now.getHours()).slice(-2)        // heures ...
                  + ("0" + now.getMinutes()).slice(-2)      // minutes ...
                  + ("0" + now.getSeconds()).slice(-2);     // secondes ...
   
    }
    
    
});