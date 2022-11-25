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

// vignere cipher
const encrypt = (message, key) => {
  let encrypted = "";
  let key_index = 0;
  for (let i = 0; i < message.length; i++) {
    let c = message[i];
    if (c.match(/[a-z]/i)) {
      let code = message.charCodeAt(i);
      if (code >= 65 && code <= 90)
        c = String.fromCharCode(
          ((code - 65 + key.charCodeAt(key_index) - 65) % 26) + 65
        );
      else if (code >= 97 && code <= 122)
        c = String.fromCharCode(
          ((code - 97 + key.charCodeAt(key_index) - 97) % 26) + 97
        );
      key_index = (key_index + 1) % key.length;
    }
    encrypted += c;
  }
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
    // timeout
    setTimeout(() => {
      sendMsg();
    }, 3000);
  });
};
