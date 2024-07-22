package core

// This file is for dispatching events. Operator commands, agent tasks, etc. Sockets * Http

import (
	"encoding/json"
	"fmt"
	"github.com/gorilla/websocket"
)

// TODO add a channel to get Message Response
func DispatchSocket(event Event, conn *websocket.Conn) {

	socketPackage := Package{
		Head: event.Head,
		Data: event.Data,
	}
	mainJsonBytes, err := json.Marshal(socketPackage)
	if err != nil {
		fmt.Println("[!] DispatchSocket Failed: binary.Write failed:", err)
	}

	err = conn.WriteMessage(websocket.BinaryMessage, mainJsonBytes)

}

// TODO The current dispatch s handled through a ResponseChan in Event... Somehow implement it better here?..
func DispatchHttp(event Event) {
	fmt.Println("[+] Dispatch Http Event")
	fmt.Println(event)
}
