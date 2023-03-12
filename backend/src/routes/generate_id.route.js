const express = require('express');
const router = express.Router();
const create_header = require('../scripts/create_header.script');
const game_controller = require('../controllers/game.controller');

// Function to assign a player id to a player
router.post('/', function(request, response) {
  console.log('\nPOST /generate_id');
  const body = { player: game_controller.addPlayer() };
  response.writeHead(200, create_header('application/json'));
  response.end(JSON.stringify(body));
});

module.exports = router;