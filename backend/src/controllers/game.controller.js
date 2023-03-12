const game = require('../models/game.model');

// Starts the game from its current state
function start() {
  return game.start();
}

function reset() {
  game.reset();
}

function addPlayer() {
  return game.addPlayer();
}

function getPlayer(id) {
  return game.getPlayer(id);
}

function numPlayers() {
  return Object.keys(game.players).length;
}

function publishFeed(message) {
  game.feed.push({time: Date.now(), message: message});
}

exports.start = start;
exports.reset = reset;
exports.addPlayer = addPlayer;
exports.getPlayer = getPlayer;
exports.numPlayers = numPlayers;
exports.publishFeed = publishFeed;
