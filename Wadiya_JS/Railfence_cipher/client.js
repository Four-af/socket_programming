const WebSocket = require("ws");
const websocket = new WebSocket("ws://localhost:5000");
const readline = require("readline");

let read_line;
let msg;

websocket.on("open", () => {
  console.log("Connected to server!");
  f1();
});

websocket.on("message", (msg) => {
  console.log("\nServer: " + msg);
  f1();
});

websocket.on("error", () => {
  console.log("Error connecting to server!");
});

const encrypt = (msg, key) => {
  let i = 0,j = 0;
  let flag = 0;
  let kk = key;
  let len = msg.length;
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
    matrix[row][col++] = msg[i];
    flag == 1 ? row++ : row--;
  }
  let cipher = "";
  for (i = 0; i < kk; i++) {
    for (j = 0; j < len; j++) {
      if (matrix[i][j] != "\n") cipher += matrix[i][j];
    }
  }
  console.log("Encrypted String: ",cipher);
  return cipher;
};

const f1 = () => {
  if (read_line) 
  read_line.close();
  read_line = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  read_line.question("Enter String: ", (m) => {
    msg = m;
    f2();
  });
};

const f2 = () => {
  if (read_line) 
  read_line.close();
  read_line = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  read_line.question("Enter Key: ", (key) => {
    cipher_msg = encrypt(msg, key);
    websocket.send(cipher_msg);
    setTimeout(f1,5000);
  });
};
