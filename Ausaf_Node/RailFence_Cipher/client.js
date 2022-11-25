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

const encrypt = (message, key) => {
  // rail fence cipher
  let encrypted = "";
  let i = 0,
    j = 0;
  let flag = 0;
  let rail = key;
  let len = message.length;
  let railMatrix = new Array(rail);
  for (i = 0; i < rail; i++) {
    railMatrix[i] = new Array(len);
    for (j = 0; j < len; j++) {
      railMatrix[i][j] = "\n";
    }
  }
  let row = 0,
    col = 0;
  for (i = 0; i < len; i++) {
    if (row == 0 || row == rail - 1) flag = 1 - flag;
    railMatrix[row][col++] = message[i];
    flag == 1 ? row++ : row--;
  }
  for (i = 0; i < rail; i++) {
    for (j = 0; j < len; j++) {
      if (railMatrix[i][j] != "\n") encrypted += railMatrix[i][j];
    }
  }
  console.log(encrypted);
  return encrypted;
};

/**
 * @description
 * Method for sending messages to server
 */
const sendMsg = () => {
  //closing the previous readline
  console.log("Enter message: ");
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
  console.log("Enter key: ");
  if (rl) rl.close();

  //creating a new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">> ", (key) => {
    encrypted_msg = encrypt(message, key);
    socket.send(encrypted_msg);
    setTimeout(() => {
      sendMsg();
    }, 3000);
  });
};
