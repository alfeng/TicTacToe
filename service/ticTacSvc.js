// Why doesn't this work?
// var app = require('express');

var express = require('express');
var app = express();

function handleGet(req, rsp)
{
    rsp.send('Hello World');
}

function serverMain()
{
    var host = server.address().address;
    var port = server.address().port;

    console.log("ticTacSvc listening at http://%s:%s", host, port);
}

app.get('/', handleGet);

var server = app.listen(8081, serverMain);

