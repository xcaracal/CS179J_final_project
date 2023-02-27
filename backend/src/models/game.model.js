const Player = require('./player.model');

const GAME_TIME = 300000; // milliseconds

let active = false;
let time = 300000; // milliseconds
let current_player_id = 1;
let players = {};

// Stops and resets the game to its default values
// This also wipes all the players currently in the game
// Players will need to reset their devices and reconnect
function reset() {
  active = false;
  time = GAME_TIME;
  current_player_id = 1;
  players = {};
}

// Add a player to the game
function addPlayer() {
  const id = current_player_id;
  current_player_id++;
  const player = new Player(id);
  players[id] = player;
  return player;
}

function getPlayer(id) {
  return players[id];
}

function json() {
  return {
    active: active,
    time: time,
    players: players
  }
}

exports.active = active;
exports.time = time;
exports.players = players;
exports.reset = reset;
exports.addPlayer = addPlayer;
exports.getPlayer = getPlayer;
exports.json = json;