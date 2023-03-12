const express = require('express');
const game_controller = require("../controllers/game.controller");
const create_header = require("../scripts/create_header.script");
const game_model = require("../models/game.model");
const router = express.Router();

router.post('/', (request, response) => {
  console.log('\nPOST /start');
  const did_start = game_controller.start();
  let game = game_model.json();
  game.did_start = did_start;
  response.writeHead(200, create_header('application/json'));
  response.end(JSON.stringify(game));
})

module.exports = router;