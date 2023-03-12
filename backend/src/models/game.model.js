const Player = require('./player.model');

const GAME_TIME = 300000; // milliseconds

let active = false;
let time = GAME_TIME; // milliseconds
let current_player_id = 1;
let players = {};
let start_time = -1;
let feed = [];

// Stops and resets the game to its default values
// This also wipes all the players currently in the game
// Players will need to reset their devices and reconnect
function reset() {
  active = false;
  time = GAME_TIME;
  current_player_id = 1;
  players = {};
  start_time = -1;
  feed.length = 0;
}

function updateTime() {
  if (start_time === -1) return;
  time = Math.max(0, GAME_TIME - (Date.now() - start_time));
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
  updateTime();
  return players[id];
}

function json() {
  updateTime();
  return {
    active: active,
    time: time,
    players: players,
    start_time: start_time,
    feed: feed
  }
}

function start() {
  if (isStarted()) return false;
  start_time = Date.now();
  return true;
}

function isStarted() {
  return start_time !== -1;
}

function isEnded() {
  return isStarted() && (Date.now() - start_time < GAME_TIME);
}

exports.active = active;
exports.time = time;
exports.players = players;
exports.feed = feed;
exports.reset = reset;
exports.addPlayer = addPlayer;
exports.getPlayer = getPlayer;
exports.json = json;
exports.start = start;
exports.isStarted = isStarted;
exports.isEnded = isEnded;