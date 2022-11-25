const { WebSocketServer } = require("ws");
const wss = new WebSocketServer({ port: 5000 });
const readline = require("readline");

let rl;

console.log("Server Listening on port 5000");

wss.on("connection", (ws) => {
  console.log("Client connected");

  ws.on("message", (message) => {
    message = message.toString();
    console.log("Message received from client: ", message);
    console.log("Enter key: ");
    getKey(message);
  });

  ws.on("close", () => {
    console.log("Client disconnected");
  });
});

//to accept key
const getKey = (message) => {
  if (rl) rl.close(); //closing previous readline

  //creating new readline
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">>", (key) => {
    decrypted_msg = decrypt(message, key);
  });
};

const decrypt = (message, key) => {
  let decrypted = "";
  key = Number(key);
  let code, new_char;

  for (i = 0; i < message.length; i++) {
    code = message.charCodeAt(i);
    new_char = message[i];
    if (code >= 65 && code <= 90) {
      new_char = String.fromCharCode(((code - 65 - key + 26) % 26) + 65);
      // console.log("New code", ((code - 65 - key) % 26) + 65);
    } else if (code >= 97 && code <= 122) {
      new_char = String.fromCharCode(((code - 97 - key + 26) % 26) + 97);
      // console.log("New code", ((code - 97 - key) % 26) + 97);
    }
    new_char = new_char.toString();
    decrypted += new_char;
  }
  console.log("Decrypted msg: " + decrypted);
  return decrypted;
};
