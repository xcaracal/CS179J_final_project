const express = require('express');
const router = express.Router();
const game_controller = require('../controllers/game.controller');
const game_model = require('../models/game.model');

router.post('/', (request, response) => {
  console.log('POST /reset');
  game_controller.reset();
  response.writeHead(200, {'Content-Type': 'application/json'});
  response.end(JSON.stringify(game_model.json()));
});

module.exports = router;