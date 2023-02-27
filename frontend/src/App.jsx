import { useState, useEffect } from 'react'
import './App.css'

function App() {

  const [players, setPlayer] = useState([
    {
        "id": 0,
        "alive": true,
        "ammo": 10,
        "points": 0 
    }
  ])
// 0: Stopped Game
// 1: Started Game
  const [gameState, setGame] = useState(0)
  const [minutes, setMinutes] = useState(5)
  const [seconds, setSeconds] = useState(0)

  useEffect(() => {
    if(gameState == 1) {
        const timer = setTimeout(() => {
            if(seconds == 0) {
                setMinutes(minutes - 1);
                setSeconds(59);
            }
            else {
                setSeconds(seconds - 1);
            }
        }, 1000)

        return () => { clearTimeout(timer)}
    }
  })
  const formatSeconds = (seconds) => {
    if(seconds < 10) {
        return "0" + seconds
    }
    else {
        return seconds;
    }
  }
  const resetGame = () => {
    fetch("http://localhost:3333/reset")
        .then(res => {console.log(res)})
        .catch(err => err);
    setGame(0)
    setMinutes(5)
    setSeconds(0)
  }
  
  const callAPI = async (option) => {
    // Option 0: Access Game Status
    if(option === 0) {
        fetch('http://localhost:3333/status')
            .then(res => {
                console.log(res);
            })
            .catch(err => err);
    }
    // Option 1: Check if Shot
    // Option 2: Check if Reloaded
  }

  return (
    <div className="App">
        <div className="timer">
            <div><h2>TIMER</h2></div>
            <div><h1>{minutes}:{formatSeconds(seconds)}</h1></div>
        </div>
        <div className="controls">
            <div><h2>Free For All</h2></div>
            <div>
                <button className="start" onClick={() => setGame(1)}>START GAME</button>
                <button className="pause" onClick={() => setGame(0)}>PAUSE GAME</button>
            </div>
            <button className="reset" onClick={() => resetGame()}>RESET GAME</button>
        </div>
        <div className="playerList">
            <h2>Players</h2>
            {players.map((player, i) => {
                return(
                <div className="playerCard" key={i}>
                    <div>ID: {player.id}</div>
                    <div>{player.alive ? "🔫" : "💀"}</div>
                    <div>{player.ammo} / 10</div>
                    <div>{player.points} points</div>
                </div>
                );
            })}
        </div>
        <div className="feed">
            <h2>Feed</h2>
            <div className="events"></div>
        </div>
    </div>
  )
}

export default App
