const PLAYER_AMMO = 10; // maximum ammo a player can have
const DEAD_TIME = 5000; // milliseconds

module.exports = class Player {
  constructor(id) {
    this.id = id;
    this.ammo = PLAYER_AMMO;
    this.alive = true;
    this.points = 420;
  }

  // Check before if the player is alive
  shoot() {
    if (this.ammo <= 0) return false;
    this.ammo--;
    return true;
  }

  reload() {
    this.ammo = PLAYER_AMMO;
    return this.ammo;
  }

  respawn() {
    this.alive = true;
    this.ammo = PLAYER_AMMO;
  }
}