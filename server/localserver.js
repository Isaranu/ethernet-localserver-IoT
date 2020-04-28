const express = require('express');
const app = express();
const port = 4000;

app.get('/', function(req, res){
    console.log('Ethernet shield connected !');
    res.status(200).send('OK');    
});

app.get('/senddata', function(req, res){
    console.log(req.query);
    res.status(200).send('Already got your data !'); 
});

app.listen(port, function(){
    console.log('Local server Ethetnet CPAL started port : ', port);
});
