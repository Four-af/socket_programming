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
    console.log("Enter key: ");
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
    // decrypt using rail fence cipher
    let decrypted = "";
    let i = 0,
      j = 0;
    let flag = 0;
    let rail = key;
    let len = message.length;
    console.log("Message length: " + len + "\n");
    let railMatrix = new Array(rail);
    //initialising rail matrix
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
      railMatrix[row][col++] = "*";
      flag == 1 ? row++ : row--;
    }
    let index = 0;
    for (i = 0; i < rail; i++) {
      for (j = 0; j < len; j++) {
        if (railMatrix[i][j] == "*" && index < len) {
          railMatrix[i][j] = message.charAt(index++);
        }
      }
    }
    row = 0;
    col = 0;
    for (i = 0; i < len; i++) {
      if (row == 0) flag = 1;
      else if (row == rail - 1) flag = 0;
      if (railMatrix[row][col] != "*") decrypted += railMatrix[row][col++];
      flag == 1 ? row++ : row--;
    }
    ws.send(decrypted);
    return decrypted;
  };

  ws.on("close", () => {
    console.log("Client disconnected");
  });
});
