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

  const decrypt = (message, key) => {
    message = message.toString();
    console.log("Message: " + message + "  Key: " + key + "\n");
    let decrypted = "";
    let key_index = 0;
    for (let i = 0; i < message.length; i++) {
      let c = message[i];
      if (c.match(/[a-z]/i)) {
        let code = message.charCodeAt(i);
        if (code >= 65 && code <= 90)
          c = String.fromCharCode(
            ((code - 65 - (key.charCodeAt(key_index) - 65) + 26) % 26) + 65
          );
        else if (code >= 97 && code <= 122)
          c = String.fromCharCode(
            ((code - 97 - (key.charCodeAt(key_index) - 97) + 26) % 26) + 97
          );
        key_index = (key_index + 1) % key.length;
      }
      decrypted += c;
    }
    console.log("Decrypted message: " + decrypted);
    return decrypted;
  };

  ws.on("close", () => {
    console.log("Client disconnected");
  });
});
