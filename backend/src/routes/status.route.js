const express = require('express');
const router = express.Router();
const create_header = require('../scripts/create_header.script');
const game_model = require('../models/game.model');

router.get('/', (request, response) => {
  console.log('GET /status');
  response.writeHead(200, create_header('application/json'));
  response.end(JSON.stringify(game_model.json()));
});

module.exports = router;