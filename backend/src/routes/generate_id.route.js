const express = require('express');
const router = express.Router();
const game_controller = require('../controllers/game.controller');

// Function to assign a player id to a player
router.post('/', function(request, response) {
  console.log('POST /generate_id');
  const body = { player: game_controller.addPlayer() };
  response.writeHead(200, {'Content-Type': 'application/json', 'Access-Control-Allow-Origin': '*'});
  response.end(JSON.stringify(body));
});

module.exports = router;