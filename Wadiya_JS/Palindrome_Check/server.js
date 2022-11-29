const { WebSocketServer } = require("ws");
const wss = new WebSocketServer({ port: 5000 });
const readline = require("readline");
console.log("Listening on port 5000");
let rl;
wss.on("connection", (ws) => {
  console.log("Client has connected");
  sendMsg();

  ws.on("message", (message) => {
    console.log("\nClient: " + message);
    if (isPalindrome(message)) {
    ws.send("Server: "+ message +" is a Palindrome!");
    console.log("Server: " + message + " is a palindrome");
    } else {
    ws.send("Server: "+ message +" is not a Palindrome!");
    console.log("Server: " + message + " is not a palindrome");
    }
    sendMsg();
  });

  ws.on("close", () => {
    console.log("Client has disconnected");
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
const sendMsg = () => {
  if (rl) rl.close();
  rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question(">> ", (msg) => {
    wss.clients.forEach((client) => {
      client.send(msg);
    });
    sendMsg();
  });
};