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
  const [feed, setFeed] = useState([])

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
  useEffect(() => {
    const timer = setTimeout(() => {
        fetch(import.meta.env.VITE_BACKEND + '/status')
            .then(response => response.json())
            .then(data => {
                setPlayer(data.players)
                setFeed(data.feed)
            } )
    }, 250)

    return () => { clearTimeout(timer)}
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
    fetch(import.meta.env.VITE_BACKEND + "/reset", {method: "POST"})
        .then(res => {console.log(res)})
        .catch(err => err);
    setGame(0)
    setMinutes(5)
    setSeconds(0)
  }

  const sortFeed = (feed) => {
    feed.sort(function(a,b) {
        var keyA = a.time;
        var keyB = b.time;
        if(keyA < keyB) return 1;
        if(keyB < keyA) return -1;
        return 0;
    })
    return feed;
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
                <button className="pause" onClick={() => setGame(0)}>DEBUG GAME</button>
            </div>
            <button className="reset" onClick={() => resetGame()}>RESET GAME</button>
        </div>
        <div className="playerList">
            <h2>Players</h2>
            {Object.keys(players).map((id) => {
                return(
                <div className="playerCard" key={id}>
                    <div>ID: {id}</div>
                    <div>{players[id].alive ? "🔫" : "💀"}</div>
                    <div>{players[id].ammo} / 10</div>
                    <div>{players[id].points} points</div>
                </div>
                );
            })}
        </div>
        <div className="feed">
            <h2>Feed</h2>
            <div className="events">{sortFeed(feed).map((object) => { return(<p key={object.time}>{object.time}: {object.message}</p>)})}</div>
        </div>
    </div>
  )
}

export default App
