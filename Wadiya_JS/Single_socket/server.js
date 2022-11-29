const { WebSocketServer } = require("ws");
const websocketserver = new WebSocketServer({ port: 5000 });
const readline = require("readline");
console.log("Listening on port 5000\n");
let read_line;
websocketserver.on("connection", (ws) => {
  console.log("Client has connected\n");
  get_msg();
  ws.on("message", (message) => {
    console.log("\nClient: " + message);
    get_msg();
  });
  ws.on("close", () => {
    console.log("Client has disconnected\n");
  });
});
const get_msg = () => {
  if (read_line) read_line.close();
  read_line = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  read_line.question("Server: ", (m) => {
      websocketserver.clients.forEach((client) => {
          client.send(m);
        });
        get_msg();
  });
};