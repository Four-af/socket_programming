const WebSocket = require("ws");
const socket = new WebSocket("ws://localhost:3000");
const readline = require("readline");
let read_line;
let message;
socket.on("open", () => {
  console.log("Connected to server");
  sendMsg();
});

socket.on("message", (message) => {
  console.log("\nServer: " + message);
  sendMsg();
});

socket.on("error", () => {
  console.log("Error connecting to server");
});


const sendMsg = () => {
    if (read_line) read_line.close();
    read_line = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });
    read_line.question(">> ", (msg) => {
    socket.send(msg);
    
    sendMsg();
    });
};