package core

import (
	"Amethyst/tasks"
	"crypto/rand"
	"encoding/hex"
	"encoding/json"
	"fmt"
	"log"
	"strconv"
)

func (t *TeamServer) CreateAgent(event Event) { // Created when an agent connects to a listener for the first time. Called through listener
	// TODO IMPORTANT ADD Listener Uri to Agent

	var NewAgentJson JsonAgentData
	err := json.Unmarshal(event.Data, &NewAgentJson)
	if err != nil {
		fmt.Println("[!] CreateAgent (json.Unmarshal) Failed")
	}

	pid, err := strconv.Atoi(NewAgentJson.PID)
	if err != nil {
		fmt.Println("[!] strconv.Atoi(PID) Failed")
	}

	/* Generate Unique ID */
	randomBytes := make([]byte, 32/2)
	_, err = rand.Read(randomBytes)
	if err != nil {
		panic(err)
	}
	// Convert the random bytes to a hexadecimal string
	uniqueId := hex.EncodeToString(randomBytes)

	/* Add Agent to Teamserver agents */
	newAgent := &Agent{
		Id:           len(t.Agents) + 1,
		Listener:     "/default", // TODO change this
		ComputerName: NewAgentJson.ComputerName,
		UserName:     NewAgentJson.Username,
		//ExternalIp:     event.Http.Request.RemoteAddr, // TODO FIX THIS IN EVENT STRUCT (NEEDS TO INCLUDE WEBSOCKET OR HTTP CONNECTION)?
		InternalIp:     NewAgentJson.InternalIp,
		WindowsVersion: NewAgentJson.WindowsVersion,
		ProcessName:    NewAgentJson.ProcessName,
		PID:            pid,
		Sleep:          10, // default sleep value
		LastCallHome:   0,
		TaskQueue:      make([]*tasks.Task, 0),
		UniqueId:       uniqueId, // TODO CHANGE THIS
	}
	t.Agents[len(t.Agents)+1] = newAgent

	if err != nil {
		log.Printf("[!] CreateAgent Failed ResponseWriter Write failed: %v", err)
	}

	test := PackageHttp{
		Head: "99", // TODO convert to hex 0x99 is UniqueId
		Data: uniqueId,
	}
	event.ResponseChan <- test

	agentBytes, err := json.Marshal(newAgent)
	if err != nil {
		fmt.Println("[!] CreateAgent Failed json.Marshal(newAgent)")
	}

	newEvent := Event{
		EventType: "socket",
		Agent:     newAgent,
		Head:      "NEW_AGENT",
		Data:      agentBytes,
	}
	GlobalEventBroker.Publish(newEvent)

}

// TODO Add UniqueId instead of AgentId CommandParser.cpp (When I'm on multi monitor)
func (t *TeamServer) AddTask(event Event) {
	var task tasks.Task
	err := json.Unmarshal(event.Data, &task)
	if err != nil {
		fmt.Println("[!] AddTask (json.Unmarshal) Failed")
	}
	fmt.Println("[+] AddTask", task)
	// Loop though Task.AgentId (Unique Id) & Add Task to TaskQueue
	t.Agents[task.AgentId].TaskQueue = append(t.Agents[task.AgentId].TaskQueue, &task)
}

func (t *TeamServer) RemoveTask(agentId int) {
	// TODO obviosly make this better
	t.Agents[agentId].TaskQueue = t.Agents[agentId].TaskQueue[1:]
}

// AgentCheckIn receives the output from a previous task and returns the new task & and args as the response.
func (t *TeamServer) AgentCheckIn(event Event) {
	var agentCheckIn CheckInTask
	responseHttp := PackageHttp{
		Head: "0",
		Data: "",
	}

	err := json.Unmarshal(event.Data, &agentCheckIn)
	if err != nil {
		fmt.Println("[!] AgentCheckIn (json.Unmarshal) Failed")
	}
	// Parse Incoming Task
	fmt.Println("Agent Check In", agentCheckIn.UniqueId, agentCheckIn.TaskId)

	// Write New Task as Response (if there is one in queue)
	for i := 0; i <= len(t.Agents); i++ {
		if agent, ok := t.Agents[i]; ok {
			if agentCheckIn.UniqueId == t.Agents[i].UniqueId {
				// Publish CheckIn Event if exists
				agentCheckIn.AgentId = i
				agentTaskJson, err := json.Marshal(agentCheckIn)
				if err != nil {
					fmt.Println("[!] AgentCheckIn AgentTaskJson Marshal Failed")
				}
				newEvent := Event{
					EventType:    "socket",
					Head:         "AGENT_TASK_RESPONSE",
					Data:         agentTaskJson,
					ResponseChan: make(chan PackageHttp),
				}
				if agentCheckIn.TaskId != "0" { // TODO FIX THIS AND ABOVE THIS IS GARBAGE
					GlobalEventBroker.Publish(newEvent)
				}
				if len(agent.TaskQueue) > 0 {
					fmt.Println("THERE IS A TASK QUEUE!", agent.TaskQueue[0])
					responseHttp.Head = strconv.Itoa(agent.TaskQueue[0].CommandId)
					responseHttp.Data = agent.TaskQueue[0].Arguments
					// Remove Task from Queue
					t.RemoveTask(agent.Id)
				}
			}
		}
	}
	event.ResponseChan <- responseHttp
	fmt.Println("[+] Sent Response To Agent: ", responseHttp)
	// TODO Add Publish. (Sent request?)
}
