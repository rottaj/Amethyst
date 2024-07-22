package core

import (
	"encoding/json"
	"fmt"
	"github.com/gorilla/websocket"
	"log"
	"time"
)

// When a new operator is connected. Execute Operator(). This will create a new event listener for that operator.

// TODO EventType should be WebSocket or HTTP.
// TODO RIGHT NOW THIS IS THE BREAD AND BUTTER THE BELOW FUNCTION IS RESPONSIBLE FOR GETTING ALL EVENTS THAT HAPPEN.. NOT GREAT.

func EventListener(conn *websocket.Conn, t *TeamServer) {
	log.Printf("[+] EventListener started")
	go func() {
		for event := range GlobalEventBroker.Subscribe() {
			// TODO Instead of Dispatch create a Handler() that will dispatch. Handler() should be apart of agent.go or operator.go or socket.go or http.go idk
			switch event.EventType {
			case "socket":
				// TODO Combine both of these?
				t.SocketHandler(event)
				DispatchSocket(event, conn) // Change the parameter to just conn.
			case "http":
				t.HttpHandler(event)
			}

		}

	}()
}

func (t *TeamServer) CreateOperator(conn *websocket.Conn) {
	operator := &Operator{
		Id:         len(t.Operators) + 1,
		Connection: conn,
		Name:       "Bruce Wayne",
	}

	t.Operators[len(t.Operators)+1] = operator

	EventListener(conn, t)

	operatorJson, _ := json.Marshal(operator)

	event := Event{
		EventType: "socket",
		Operator:  operator,
		Head:      "OPERATOR_CONNECTED",
		Data:      operatorJson,
	}
	log.Printf("[+] CreateOperator Created Operator: %s", operator.Name)
	time.Sleep(1000) // Workaround.. Sometimes Publish doesn't work.... must have to wait for socket to complete.
	GlobalEventBroker.Publish(event)
}

func (t *TeamServer) RemoveOperator(operatorId int) {
	fmt.Println("RemoveOperator() requested")
}
