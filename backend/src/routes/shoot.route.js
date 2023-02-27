const express = require('express');
const Joi = require('joi');
const router = express.Router();
const create_header = require('../scripts/create_header.script');
const handle = require('../scripts/schema_handle.script');
const game_controller = require('../controllers/game.controller');
const player_controller = require('../controllers/player.controller');

router.post('/', function(request, response) {
  console.log('POST /shoot');
  const schema = Joi.object({
    id: Joi.number().integer()
      .min(1)
      .max(game_controller.numPlayers())
      .required()
  });

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
  if (!player.alive) {
    response.writeHead(200, create_header('text/plain'));
    response.end(`ID ${id} is dead`);
    return;
  }

  const shot = player_controller.shoot(player);
  response.writeHead(200, create_header('text/plain'));
  response.end(`ID ${id} ${shot ? 'shoots' : 'is out of ammo'}`);
});

module.exports = router;
