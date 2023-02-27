const express = require('express');
const router = express.Router();
const game_model = require('../models/game.model');

router.get('/', (request, response) => {
  console.log('GET /status');
  response.writeHead(200, {'Content-Type': 'application/json'});
  response.end(JSON.stringify(game_model.json()));
});

module.exports = router;