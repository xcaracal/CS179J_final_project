var express = require('express');

const PORT = 3333;

var app = express();
app.use(express.urlencoded());

var current_player_pointer = 1;

app.get('/', function(request, response) {
  console.log('GET /');
  const TEXT = 'Team n=4 Laser Tag Backend';
  response.writeHead(200, {'Content-Type': 'text/plain'});
  response.end(TEXT);
});

app.listen(PORT);
console.log(`Listening at http://localhost:${PORT}`)
