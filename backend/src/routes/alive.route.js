const express = require('express');
const Joi = require('joi');
const router = express.Router();
const handle = require('../scripts/schema_handle.script');
const create_header = require('../scripts/create_header.script');
const game_controller = require('../controllers/game.controller');
const player_controller = require('../controllers/player.controller');

const schema = Joi.object().keys({
  id: Joi.number().required()
});

// Force the player to be alive
router.post('/', (request, response) => {
  console.log('\nPOST /dead');

  const { error, value } = handle(request, response, schema);
  if (error) return;

  const id = value.id;
  const player = game_controller.getPlayer(id);

  // Check if the player is valid
  if (player === undefined) {
    response.writeHead(400, create_header('text/plain'));
    response.end('Invalid ID specified.');
    return;
  }

  // Check if the player is alive
  if (player.alive) {
    response.writeHead(200, create_header('text/plain'));
    response.end(`ID ${id} is already alive.`);
    return;
  }

  player_controller.alive(player);
  response.writeHead(200, create_header('text/plain'));
  response.end(`ID ${id} set to alive.`);
});

module.exports = router;