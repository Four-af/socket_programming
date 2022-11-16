const { WebSocketServer } = require("ws");
const wss = new WebSocketServer({ port: 8080 });
const readline = require("readline");

console.log("Listening on port 8080");

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

  //first message trigger
  sendMsg();

  ws.on("message", (message) => {
    console.log("\nClient: " + message);

    // check if the message is a palindrome
    if (isPalindrome(message)) {
      // show message in client side
      ws.send("Server: " + message + " is a palindrome");
      // console.log("Server: " + message + " is a palindrome");
    } else {
      // console.log("Server: " + message + " is not a palindrome");
      ws.send("Server: " + message + " is not a palindrome");
    }

    //message trigger for every message received from client for continuous chat
    sendMsg();
  });

  ws.on("close", () => {
    console.log("Client disconnected");
  });
});

const isPalindrome = (str) => {
  let len = str.length;
  for (let i = 0; i <= len / 2; i++) {
    if (str[i] !== str[len - 1 - i]) {
      return false;
    }
  }
  return true;
};

/**
 * @description
 * Method for sending messages to client
 */
const sendMsg = () => {
  //closing the previous readline
  if (rl) rl.close();

  //creating a new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">> ", (msg) => {
    wss.clients.forEach((client) => {
      client.send(msg);
    });

    //message trigger for every message sent from server for continuous chat
    sendMsg();
  });
};
