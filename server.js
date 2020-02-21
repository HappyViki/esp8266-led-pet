var express = require('express');
var app = express();
var foodBasket = []

app.use(express.static('public'))

console.log("Go to http://localhost:8080/ in your browser and click the carrot button.");

app.get('/put_food_into_basket', function (request, response) {
  var food = (request.query.choice || '').toLowerCase()
  console.log("put_food_into_basket",food);
  if (food) {
    foodBasket.push(food)
    response.send("I put " + food + " in my basket.")
  } else {
    response.send("You said you gave me food, there was no food given.")
  }
})
app.get('/feed_pet_from_basket', function (request, response){
  //var clientIp = request.headers["X-Forwarded-For"] || request.connection.remoteAddress;
  var food = (foodBasket.pop() || '').toLowerCase()
  console.log("feed_pet_from_basket",food);
  if (food) {
    response.send(food)
  } else {
    response.send("Sorry, no food for you.")
  }
})
app.listen(8080);
