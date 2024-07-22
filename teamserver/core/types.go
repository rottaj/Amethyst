package core

import (
	"Amethyst/tasks"
	"github.com/gorilla/websocket"
	"net/http"
)

type CheckInTask struct { // Uses in response to CheckIn
	UniqueId   string `json:"Id"`
	AgentId    int    // This is just for testing. Will be replace in DB implementation.
	TaskId     string `json:"TaskId"`
	TaskArgs   string `json:"TaskArgs"`
	TaskOutput string `json:"TaskOutput"`
}

/* Used with JSON.Marshal() to serialize the request body */
type JsonAgentData struct {
	Username       string `json:"Username"`
	ComputerName   string `json:"ComputerName"`
	ProcessName    string `json:"ProcessName"`
	InternalIp     string `json:"InternalIp"`
	PID            string `json:"PID"`
	WindowsVersion string `json:"WindowsVersion"`
}

type Agent struct { // This is the stub running on an infected computer.
	Id             int    // Used for basic querying, indexing, etc.
	UniqueId       string // Stored on stub. Sent with CallHome
	Listener       string
	ComputerName   string
	UserName       string
	ExternalIp     string
	InternalIp     string
	WindowsVersion string
	PID            int
	ProcessName    string
	Sleep          int
	LastCallHome   int // set to datetime
	TaskQueue      []*tasks.Task
}

type Operator struct { // This is an operator that can login to the C2
	Id         int
	Name       string
	Connection *websocket.Conn // Later, loop through and emit to each connection.
}

type Listener struct {
	Id   int
	Name string
	Host string
	Port int
	Uri  string
}

type TeamServer struct { // This is a singleton for the C2 teamserver
	Port           int
	AgentServer    *http.Server
	OperatorServer *http.Server
	Agents         map[int]*Agent
	Operators      map[int]*Operator
	Listeners      map[int]*Listener
}
