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
  const [feed, setFeed] = useState([])
  const [millis, setMillis] = useState(300000);

  useEffect(() => {
    const timer = setTimeout(() => {
        fetch(import.meta.env.VITE_BACKEND + '/status')
            .then(response => response.json())
            .then(data => {
                setPlayer(data.players)
                setFeed(data.feed)
                setMillis(data.time);
            } )
    }, 250)

    return () => { clearTimeout(timer)}
  })

  function millisToMinutesAndSeconds(ms) {
    const minutes = Math.floor(ms / 60000);
    const seconds = ((ms % 60000) / 1000).toFixed(0);
    return minutes + ":" + (seconds < 10 ? '0' : '') + seconds;
  }

  const resetGame = () => {
    fetch(import.meta.env.VITE_BACKEND + "/reset", {method: "POST"})
        .then(res => {console.log(res)})
        .catch(err => err);
  }

  function timeConverter(UNIX_timestamp){
    var a = new Date(UNIX_timestamp);
    var months = ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'];
    var year = a.getFullYear();
    var month = months[a.getMonth()];
    var date = a.getDate();
    var hour = a.getHours();
    var min = a.getMinutes();
    var sec = a.getSeconds();
    var time = date + ' ' + month + ' ' + year + ' ' + String(hour).padStart(2, '0') + ':' + String(min).padStart(2, '0') + ':' + String(sec).padStart(2, '0') ;
    return time;
  }

  const startGame = () => {
    let status = {};
    fetch(import.meta.env.VITE_BACKEND + "/start", {method: "POST"})
      .then(res => {console.log(res); status = res;})
      .catch(err => err);
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
            <div><h1>{millisToMinutesAndSeconds(millis)}</h1></div>
        </div>
        <div className="controls">
            <div><h2>Free For All</h2></div>
            <div>
                <button className="start" onClick={() => startGame()}>START GAME</button>
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
                </div>
                );
            })}
        </div>
        <div className="feed">
            <h2>Feed</h2>
            <div className="events">{sortFeed(feed).map((object) => { return(<p key={object.time}>{timeConverter(object.time)}: <b>{object.message}</b></p>)})}</div>
        </div>
    </div>
  )
}

export default App
