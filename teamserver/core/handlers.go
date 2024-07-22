package core

import (
	"fmt"
)

func (t *TeamServer) HttpHandler(event Event) {
	fmt.Println("[+] HttpHandler: ", event.Head)
	switch event.Head {
	case "Init":
		t.CreateAgent(event)
	case "CheckIn":
		t.AgentCheckIn(event)
	}
}

func (t *TeamServer) SocketHandler(event Event) {
	fmt.Println("[+] SocketHandler ", event.Head)
	switch event.Head {
	case "AGENT_TASK":
		t.AddTask(event) // TODO Replace message with task{}
	}
	//case "NEW_LISTENER_CREATED":
	//t.CreateNewListener(jsonData)
}
