const WebSocket = require("ws");
const websocket = new WebSocket("ws://localhost:3000");
const readline = require("readline");
let read_line;
let exist = false;
let i;
websocket.on("open", () => {
  console.log("-------------------Connected to server-------------------");
});

websocket.on("message", (data) => {
  const payload = JSON.parse(data);
  const method = payload.method;
  if (method === "get id") {
    i = payload.id;
    get_Sender();
  }
  else if (method === "chat message") {
    console.log(`\n${payload.name}: ${payload.msg}`);
    if (!exist) get_Sender();
    else send_message();
  }
});

websocket.on("error", () => {
  console.log("-------------------Error Connecting to Server-------------------");
});

websocket.on("close", () => {
  console.log("\n-------------------Server got disconnected-------------------");
  process.exit();
});

const send_message = () => {
  if (read_line) 
  read_line.close();
  read_line = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  read_line.question(">> ", (msg) => {
    const payload = {
      method: "chat message",
      msg,
      id: i,
    };
    websocket.send(JSON.stringify(payload));
    send_message();
  });
};
const get_Sender = () => {
  if (read_line) 
  read_line.close();
  read_line = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  read_line.question("Enter Username: ", (name) => {
    const payload = {
      method: "new user",
      name,
      id: i,
    };
    websocket.send(JSON.stringify(payload));
    exist = true;
    console.log("-------------------You've entered the global chat-------------------");
    send_message();
  });
};

