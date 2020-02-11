const http = require('http');
var express = require('express');
var app = express();
var foodBasket = []

app.use(express.static('public'))

app.get('/feed', function (request, response) {
  //var clientIp = request.headers["X-Forwarded-For"] || request.connection.remoteAddress;
  //console.log(clientIp);
  //console.log(response);
  if (request.query.choice) {
    console.log("Storing food:",request.query.choice);
    foodBasket.push(request.query.choice.toLowerCase())
  } else if (foodBasket.length) {
    console.log("Sending food:",foodBasket.pop());
    response.send("carrot")
  } else {
    response.send("empty")
  }
})

app.listen(8080);
