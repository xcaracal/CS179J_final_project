const express = require('express');

// View routes
const status_route = require('./routes/status.route');
const reset_route = require('./routes/reset.route');
const start_route = require('./routes/start.route');

// User routes
const generate_id_route = require('./routes/generate_id.route');
const shoot_route = require('./routes/shoot.route');
const reload_route = require('./routes/reload.route');
const alive_route = require('./routes/alive.route');
const dead_route = require('./routes/dead.route');

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
app.use('/status', status_route);
app.use('/reset', reset_route);
app.use('/start', start_route)
app.use('/generate_id', generate_id_route);
app.use('/shoot', shoot_route);
app.use('/reload', reload_route);
app.use('/alive', alive_route);
app.use('/dead', dead_route);

app.listen(PORT);
console.log(`Listening at http://localhost:${PORT}`)
