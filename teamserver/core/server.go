package core

import (
	"net/http"
	"strconv"
)

func InitializeTeamServer() TeamServer { // This initializes a team core and database file
	var t = TeamServer{
		Port:        8081,
		AgentServer: &http.Server{Addr: ":" + strconv.Itoa(8081), Handler: nil /*Replace with default handler */},
		Agents:      make(map[int]*Agent),
		Operators:   make(map[int]*Operator),
		Listeners:   make(map[int]*Listener),
	}
	return t
}

func (t *TeamServer) CreateListener(sEndpoint string) { // Created by Operator through CLI. Creates a new Listener & Endpoint
	pListener := &Listener{Id: len(t.Listeners) + 1, Uri: sEndpoint}
	t.Listeners[len(t.Listeners)+1] = pListener
}

// OperatorAuthenticate (Used when a operator connects)

// GetSystemPackages
// Get's mingw for compiling agent.exe
