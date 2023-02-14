const express = require('express');
const generateIdRoute = require('./routes/generateId.route');
const shootRoute = require('./routes/shoot.route');

const PORT = 3333;

const app = express();
app.use(express.urlencoded());

app.get('/', function(request, response) {
  console.log('GET /');
  const TEXT = 'Team n=4 Laser Tag Backend';
  response.writeHead(200, {'Content-Type': 'text/plain'});
  response.end(TEXT);
});

// ROUTES
app.use('/generate_id', generateIdRoute);
app.use('/shoot', shootRoute);

app.listen(PORT);
console.log(`Listening at http://localhost:${PORT}`)
