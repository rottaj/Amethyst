package core

import (
	"encoding/base64"
	"encoding/json"
	"fmt"
	"github.com/gorilla/mux"
	"log"
	"net/http"
)

type PackageHttp struct {
	Head string
	Data string
}

type Package struct {
	Head string          `json:"Head"`
	Data json.RawMessage `json:"Data"`
}

func (t *TeamServer) DefaultHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)

	log.Printf("HttpHandler: %s", vars["data"])

	sDec, _ := base64.StdEncoding.DecodeString(vars["data"])
	log.Printf("Decoded: %s", string(sDec))

	var data Package
	err := json.Unmarshal(sDec, &data)
	if err != nil {
		fmt.Println("[!] DefaultHandler Failed json.Unmarshal.")
	}

	t.DefaultAgentListenerHandler(w, r, data)
}

// TODO UPDATE ALL TO ONLY GET REQUESTS WITH BASE64 ENCODED JSON
func (t *TeamServer) DefaultAgentListenerHandler(w http.ResponseWriter, r *http.Request, agentPackage Package) {
	newEvent := Event{
		EventType:    "http",
		Head:         agentPackage.Head,
		Data:         agentPackage.Data,
		ResponseChan: make(chan PackageHttp),
	}

	GlobalEventBroker.Publish(newEvent)

	// Receive Response From Channel (ResponseData)
	res := <-newEvent.ResponseChan

	responseJSON, err := json.Marshal(res)
	if err != nil {
		http.Error(w, "Internal Server Error", http.StatusInternalServerError)
		return
	}

	// Send Response to Agent
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)
	w.Write(responseJSON)

}

func (t *TeamServer) Start() {
	// Refactor this. Add the ability to create, edit, and delete listeners.
	r := mux.NewRouter()
	r.HandleFunc("/default-{data}", t.DefaultHandler)
	http.ListenAndServe(":8081", r)
	//t.AgentServer.ListenAndServe(":80", r)
}

// Stops the HTTP core
func Stop(h *http.Server) {

}

// Restart (will be needed to add new listener probably idk)
