package core

import (
	"encoding/json"
	"flag"
	"fmt"
	"github.com/gorilla/websocket"
	"log"
	"net/http"
)

// #TODO This file is meant for socket programming used between operator commands and teamserver.

//var addr = flag.String("addr", "localhost:9998", "http service address")

// TODO ADDING ON TO MY COMMENT ABOVE, I NEED TO ADD HEAD. FIX in "Controller.c" in client (Then add a Global Socket controller function (takes in key value and yadayada).
type AgentTaskPackageData struct {
	AgentId   int    `json:"AgentId"`
	Arguments string `json:"Arguments"`
	CommandId int    `json:"CommandId"`
}

var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
}

func (t *TeamServer) ConnectionHandler(w http.ResponseWriter, r *http.Request) {
	/* Emit new Operator to clients. */
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("[!] InitHandler Failed: Upgrade Failed: ", err)
		return
	}
	t.CreateOperator(conn)
	// TODO MOVE TO OTHER FUNCTION (SocketListener)
	for {
		_, message, err := conn.ReadMessage()
		if err != nil {
			log.Println("[!] InitHandler Failed: ReadMessage() Failed: ", err)
			break
		}
		log.Printf("[+] ConnectionHandler New Message %s", string(message))

		var jsonData Package

		err = json.Unmarshal(message, &jsonData)
		if err != nil {
			fmt.Println("[!] EmitHandler Failed: json.Unmarshal(message) failed")
		}

		event := Event{
			EventType: "socket",
			Head:      jsonData.Head,
			Data:      jsonData.Data,
		}

		log.Printf("[+] ConnectedHandler New Socket Event. Head: %s", event.Head)
		GlobalEventBroker.Publish(event)
	}
}

// TODO Build switch chase for Message()

func (t *TeamServer) InitializeWebSocketOperatorServer() {

	flag.Parse()
	log.SetFlags(0)
	http.HandleFunc("/amethyst-operator", t.ConnectionHandler)
	log.Fatal(http.ListenAndServe(":9998", nil))
}
