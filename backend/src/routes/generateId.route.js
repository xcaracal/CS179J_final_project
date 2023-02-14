const express = require('express');
const router = express.Router();
const controller = require('../controllers/id.controller');

// Function to assign a player id to a player
router.post('/', function(request, response) {
  console.log('POST /generate_id');
  response.writeHead(200, {'Content-Type': 'application/json'});
  response.write({'id': controller.current_player_id});
  response.end();
  controller.current_player_id++; // Increment player pointer
});

module.exports = router;