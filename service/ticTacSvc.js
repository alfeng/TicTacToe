// Sample code from:
// https://www.tutorialspoint.com/nodejs/nodejs_express_framework.htm

// Why doesn't this work?
// var app = require('express');
var express = require('express');
var app = express();

// Hello handler
function handleGet_Hello(req, rsp)
{
//    rsp.send('Hello World');
    rsp.send(JSON.stringify({message: 'Hello World'}));
}
app.get('/tic-tac-toe/hello', handleGet_Hello);

// Server entry point
function serverMain()
{
    var host = server.address().address;
    var port = server.address().port;

    console.log("ticTacSvc listening at http://%s:%s", host, port);
}
var server = app.listen(8081, serverMain);

// Use middleware to set default content type for all requests
function setDefaultContentType(req, rsp, next)
{
    res.header('Content-Type', 'application/json');
    next();
}
app.use('/json', setDefaultContentType);

