const { WebSocketServer } = require("ws");
const wss = new WebSocketServer({ port: 3000 });
const readline = require("readline");

console.log("Listening on port 3000");

let read_line;
let message;
wss.on("connection", (ws) => {
  console.log("Client has connected");
  sendMsg();
  ws.on("message", (message) => {
    console.log("\nClient: " + message);

 
    const check_int = new RegExp(/^[-+]?[0-9]+$/);
    const check_float = new RegExp(/^[-+]?[0-9]+\.[0-9]+$/);
    const check_alphabets = new RegExp(/^[a-zA-Z ]+$/);
    const check_special = new RegExp(
      /[`!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]/
    );

    if (check_int.test(message)) {
     ws.send("Integer");
    } else if (check_float.test(message)) {
      console.log("Float");
    } else if (check_alphabets.test(message)) {
      console.log("Alphabets");
    } else if (check_special.test(message)) {
      console.log("Special Characters");
    } else {
      console.log("No condition found!");
    }
    sendMsg();
  });

  ws.on("close", () => {
    console.log("Client has disconnected");
  });
});

const sendMsg = () => {
  if (read_line) read_line.close();
  read_line = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  read_line.question(">> ", (msg) => {
    wss.clients.forEach((client) => {
      client.send(msg);
    });
    sendMsg();
  });
};