const WebSocket = require("ws");
const socket = new WebSocket("ws://localhost:5000");
const readline = require("readline");

//singleton readline interface
let rl;
let message;

/**
 * @description
 * 1. socket.on('open') is triggered when the client is connected to the server
 * 2. socket.on('message') is triggered when the client receives a message from the server
 * 3. socket.on('error') is triggered when the client encounters an error
 */
socket.on("open", () => {
  console.log("Connected to server");

  sendMsg();
});

socket.on("message", (message) => {
  console.log("\nServer: " + message);
  //message trigger for every message received from server for continuous chat
  sendMsg();
});

socket.on("error", () => {
  console.log("Error connecting to server");
});

// substitution_cipher
const encrypt = (message, key) => {};
/**
 * @description
 * Method for sending messages to server
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
    message = msg;
    //message trigger for every message sent from client for continuous chat
    sendMsg1();
  });
};

const sendMsg1 = () => {
  //closing the previous readline
  if (rl) rl.close();

  //creating a new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">> ", (key) => {
    encrypted_msg = encrypt(message, key);
    socket.send(encrypted_msg);

    sendMsg();
  });
};
