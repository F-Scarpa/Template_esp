import { useState, useEffect} from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'

//App get caleld multiple times in react
function App() {
  const [btnState, setBtnState] = useState(true);
  const [message, setMessage] = useState("");
  const [ledOn, setLedOn] = useState(false);


  const switchLed = async (is_on: boolean) => {
    const payload = { is_on } ;
    const webResult = await fetch("/api/toggle-led", {
      method: "POST",
      body: JSON.stringify(payload)

    });                 //if a response is received then we change state of ledOn, react only change the graphics
                        //but dont really control the I/O
    if(!webResult.ok)
    {
      console.error(webResult.statusText);
      return;
    }
    setLedOn(is_on);
  }

  const getLedText = () => {
    return ledOn ? "LED is on" : "LED is off";
  }

  const getHelloWorld = async () =>     //js function for texting purpose
  {
                                                                              //before it was : 
    const webResult = await fetch("/api/hello-world");   //const webResult = await fetch("http://my-esp32.local/api/hello-world"); 
    const MyText = await webResult.text();
    setMessage(MyText);
    console.log(MyText);
  }

  const getWebSocketUrl = (suffix: string) =>
  {
    const l = window.location;
    return ((l.protocol == "https:" ? "wss://":  "ws://") + l.host + l.pathname + suffix);
  }


  //server creates JSON object which wil lbe read from the websocket

  const webSocket = () => 
  {
    const socket = new WebSocket(getWebSocketUrl("ws"));    //create new websocket
    socket.onopen = () =>        //on opened websocket
    {
      socket.send("Hello esp32");
    }
    socket.onmessage = (event) =>       //server send data to client
    {
      console.log(event.data);    //event.data is data the server received
      try{
        const attemptedBtnState = JSON.parse(event.data);
        setBtnState(attemptedBtnState.btn_state);       //btn_state is built from server with cJSON
      }
      finally {
        
      }
    }
    socket.onerror = (err) =>     //catch errors on ws
    {
      console.error(err);
    };
    socket.onclose = (event) =>     //ws get closed
    {
      console.log(event);
    }
  }
  


  /*
    to avoid Cors error and faster testing 
    - vitejs.dev
    -search proxy
    -go to server.proxy
    -go to site > viteconfig.ts

    -  server:{
    proxy:{
      "/api":{
        target: "http://my-esp32.local/",
        "changeOrigin":true
      }

    -delete http://my-esp32.local part from funcions to call
  */

  useEffect
  (
    () => {
        getHelloWorld();      //1. callback func
        webSocket();
      },         
    []                //2. when to update or run this func [] = run only once when component is rendered
  )
  //when App component is rendered getHelloWorld will be called only once


  


  return (
    <>
      <div>
        <a href="https://vite.dev" target="_blank">
          <img src={viteLogo} className="logo" alt="Vite logo" />
        </a>
        <a href="https://react.dev" target="_blank">
          <img src={reactLogo} className="logo react" alt="React logo" />
        </a>
      </div>
      <h1>ESP32</h1>
      <h1>
        {message}
      </h1>
      <div className="card">
        <button 
          style={{backgroundColor: ledOn ? 'lightblue' : ""}} 
          onClick={() => switchLed((!ledOn))}>
          {getLedText()}
        </button>
        <div style = {{
          width: "50px",
          height: "50px",
          border: "1px solid black", 
          margin: "auto",
          borderRadius: "50px",
          marginTop : "16px",
          backgroundColor: btnState ? 'pink' : "",
          }}>

        </div>
      </div>
  
    </>
  )
}

export default App
