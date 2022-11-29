const WebSocket = require("ws");
const socket = new WebSocket("ws://localhost:5000");
const readline = require("readline");

let rl;

socket.on("open", () => {
  console.log("Connected to server");
  sendmsg1();
});

socket.on("error", () => {
  console.log("Error connecting to server");
});

//to accept message
const sendmsg1 = () => {
  console.log("Enter message: ");
  if (rl) rl.close(); //closing previous readline

  //creating new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">>", (message) => {
    console.log("Enter key: ");
    sendmsg2(message);
  });
};

//to accept key
const sendmsg2 = (message) => {
  if (rl) rl.close(); //closing previous readline

  //creating new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">>", (key) => {
    encrypted_msg = encrypt(message, key);
    socket.send("" + encrypted_msg);
    sendmsg1();
  });
};

const encrypt = (message, key) => {
  let encrypted = "";
  key = Number(key);
  let code, new_char;

  for (i = 0; i < message.length; i++) {
    code = message.charCodeAt(i);
    new_char = message[i];
    if (code >= 65 && code <= 90) {
      new_char = String.fromCharCode(((code - 65 + key) % 26) + 65);
    } else if (code >= 97 && code <= 122) {
      new_char = String.fromCharCode(((code - 97 + key) % 26) + 97);
    }
    encrypted += new_char;
  }
  console.log("Encrypted msg: " + encrypted);
  return encrypted;
};
