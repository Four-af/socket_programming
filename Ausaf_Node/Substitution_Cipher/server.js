const { WebSocketServer } = require("ws");
const wss = new WebSocketServer({ port: 5000 });
const readline = require("readline");

console.log("Listening on port 5000");

//singleton readline
let rl;

/**
 * @description
 * 1. wss.on('connection') is triggered when the client is connected to the server
 * 2. ws.on('message') is triggered when the client sends a message to the server
 * 3. ws.on('close') is triggered when the client is disconnected from the server
 */
wss.on("connection", (ws) => {
  console.log("Client connected");

  ws.on("message", (message) => {
    console.log("\nClient: " + message);
    //pass the message to getKey() function which will later call decrypt function
    getKey(message);
  });

  //To accept key
  const getKey = (message) => {
    //closing the previous readline
    if (rl) rl.close();

    //creating a new readline
    rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });
    rl.question(">> ", (key) => {
      decrypted_msg = decrypt(message, key);
    });
  };

  const decrypt = (message, key) => {};

  ws.on("close", () => {
    console.log("Client disconnected");
  });
});
