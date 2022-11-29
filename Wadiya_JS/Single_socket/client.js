const WebSocket = require("ws");
const websocket = new WebSocket("ws://localhost:5000");
const readline = require("readline");
let read_line;
websocket.on("open", () => {
  console.log("Connected to server!\n");
  get_msg();
});
websocket.on("message", (msg) => {
  console.log("Server: " + msg);
  get_msg();
});
websocket.on("error", () => {
  console.log("Error connecting to server!\n");
});

const get_msg = () => {
  if (read_line) 
  read_line.close();
  read_line = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  read_line.question(": ", (m) => {
    websocket.send(m);
    get_msg();
  });
 
};
