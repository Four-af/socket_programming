const { WebSocketServer } = require("ws");
const websocketserver = new WebSocketServer({ port: 3000 });
const { v4: uuid } = require("uuid");
console.log("-------------------Listening on port 3000-------------------");
const clients = {};
websocketserver.on("connection", (ws) => {
  const id = uuid();
  clients[id] = { name: null, ws };
  const json = {
    method: "get id",
    id,
  };
  ws.send(JSON.stringify(json));

  ws.on("message", (data) => {
    const json = JSON.parse(data);
    const method = json.method;
    if (method === "new user") {
      const name = json.name;
      const i = json.id;
      clients[i].name = name;
      console.log(`${name} has connected!`);
      send_msg(i, "has joined the group chat!");
    }
    else if (method === "chat message") {
      const msg = json.msg;
      const i = json.id;
      send_msg(i, msg);
    }
  });

  ws.on("close", () => {
    const name = clients[id].name;
    if (!name) return;
    console.log(`${name} has disconnected!`);
    delete clients[id];
    Object.keys(clients).forEach((clientId) => {
      const json = {
        method: "chat message",
        msg: "has left the group chat!",
        name,
      };
      clients[clientId].ws.send(JSON.stringify(json));
    });
  });
});

const send_msg = (i, msg) => {
  const sender = clients[i].name;
  const receivers = Object.keys(clients).filter((id) => id !== i);
  receivers.forEach((clientId) => {
    const json = {
      method: "chat message",
      msg,
      name: sender,
    };
    clients[clientId].ws.send(JSON.stringify(json));
  });
};