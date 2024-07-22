package core

import (
	"Amethyst/tasks"
)

// Shamelessly copied from sliver.
// This file is for any incoming events. Can be operator commands, agent checkins, log events, etc.

// The event is determined by the EventType string. Agent, Task, or Operator can be null but 1 has to be atleast non-null.

type Event struct {
	EventType    string // Determine what the event is happening. The header to the event.
	Agent        *Agent
	Task         *tasks.Task
	Operator     *Operator
	Head         string
	Data         []byte // JSON byte array. (List of types found in types.go)
	Err          error
	ResponseChan chan PackageHttp
}

type EventBroker struct {
	stop        chan struct{}
	publish     chan Event
	subscribe   chan chan Event
	unsubscribe chan chan Event
}

// Start - Start a broker channel
func (broker *EventBroker) Start() {
	subscribers := map[chan Event]struct{}{}
	for {
		select {
		case <-broker.stop:
			for sub := range subscribers {
				close(sub)
			}
			return
		case sub := <-broker.subscribe:
			subscribers[sub] = struct{}{}
		case sub := <-broker.unsubscribe:
			delete(subscribers, sub)
		case event := <-broker.publish:
			for sub := range subscribers {
				sub <- event
			}
		}
	}
}

// Publish - Push a message to all subscribers
func (broker *EventBroker) Publish(event Event) {
	//fmt.Println("Publishing New Event: ", event.EventType)
	broker.publish <- event
}

// Subscribe - Generate a new subscription channel

// TODO WHAT THE FUCK IS THIS DOING? EXACTTLY?
func (broker *EventBroker) Subscribe() chan Event {
	events := make(chan Event)
	broker.subscribe <- events
	return events
}

// Unsubscribe - Remove a subscription channel
func (broker *EventBroker) Unsubscribe(events chan Event) {
	broker.unsubscribe <- events
	close(events)
}

func NewEventBroker() *EventBroker {
	broker := &EventBroker{
		stop:        make(chan struct{}),
		publish:     make(chan Event),
		subscribe:   make(chan chan Event),
		unsubscribe: make(chan chan Event),
	}
	go broker.Start()
	return broker
}

// TODO Move to teamserver
var (
	// EventBroker - Distributes event messages
	GlobalEventBroker = NewEventBroker()
)
