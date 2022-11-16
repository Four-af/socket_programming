const WebSocket = require("ws");
const socket = new WebSocket("ws://localhost:5000");
const readline = require("readline");
let rl;
socket.on("open", () => {
  console.log("Connected to Server");
  sendMsg();
});
socket.on("message",(message)=>{
    console.log(""+message);
    
});
socket.on("error", () => {
  console.log("Error occured while connecting to server");
});

const sendMsg = () => {
  if (rl) rl.close();
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question("Type a number: ", (msg) => {
    socket.send(msg);
    sendMsg();
  });
};