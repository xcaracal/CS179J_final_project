const game = require('../models/game.model');

let lastTickTime = -1; // The millisecond timestamp of the last tick time

// The game loop
function tick() {

}

// Starts the game from its current state
function start() {

}

// Pauses the game at its current state
function stop() {

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

exports.start = start;
exports.stop = stop;
exports.reset = reset;
exports.addPlayer = addPlayer;
exports.getPlayer = getPlayer;
exports.numPlayers = numPlayers;
