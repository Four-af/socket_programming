const { WebSocketServer } = require("ws");
const websocketserver = new WebSocketServer({ port: 5000 });
const readline = require("readline");
console.log("Listening on port 5000");
let read_line;
websocketserver.on("connection", (ws) => {
  console.log("Client has connected");
  ws.on("message", (message) => {
    console.log("\nClient: " + message);
    input_key(message);
  });

  const input_key = (message) => {
    if (read_line) 
    read_line.close();
    read_line = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
    });
    read_line.question("Enter key: ", (key) => {
      cipher_msg = decrypt(message, key);
    });
  };

  const decrypt = (message, key) => {
    message = message.toString();
    let i = 0,j = 0;
    let flag = 0;
    let kk = key;
    let len = message.length;
    let matrix = new Array(kk);
    for (i = 0; i < kk; i++) {
      matrix[i] = new Array(len);
      for (j = 0; j < len; j++) {
        matrix[i][j] = "\n";
      }
    }

    let row = 0,col = 0;
    for (i = 0; i < len; i++) {
      if (row == 0 || row == kk - 1) flag = 1 - flag;
      matrix[row][col++] = "*";
      flag == 1 ? row++ : row--;
    }
    let index = 0;
    for (i = 0; i < kk; i++) {
      for (j = 0; j < len; j++) {
        if (matrix[i][j] == "*" && index < len) {
          matrix[i][j] = message.charAt(index++);
        }
      }
    }
    row = 0;
    col = 0;
    let cipher = "";
    for (i = 0; i < len; i++) {
      if (row == 0) flag = 1;
      else if (row == kk - 1) flag = 0;
      if (matrix[row][col] != "*") cipher += matrix[row][col++];
      flag == 1 ? row++ : row--;
    }
    console.log("Original message:",cipher);
    ws.send(cipher);
    return cipher;
  };

  ws.on("close", () => {
    console.log("Client has disconnected");
  });
});