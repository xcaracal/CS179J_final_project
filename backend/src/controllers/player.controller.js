const game_controller = require('./game.controller');

function shoot(player) {
  const did_shoot = player.shoot();
  if (did_shoot) game_controller.publishFeed(`Player ${player.id} shot.`)
  return did_shoot;
}

function reload(player) {
  const did_reload = player.reload();
  if (did_reload) game_controller.publishFeed(`Player ${player.id} reloaded.`);
  return did_reload;
}

function dead(player) {
  if (player.alive) game_controller.publishFeed(`Player ${player.id} died.`);
  player.dead();
}

function alive(player) {
  if (!player.alive) game_controller.publishFeed(`Player ${player.id} respawned.`);
  player.respawn();
}

exports.shoot = shoot;
exports.reload = reload;
exports.dead = dead;
exports.alive = alive;