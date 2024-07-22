package tasks

type Task struct {
	AgentId   int    `json:"agentId"` // Agent Unique ID
	CommandId int    `json:"CommandId"`
	Arguments string `json:"Arguments"`
	Mnemonic  string
}

// This is mainly for reference.
var (
	LS        = Task{CommandId: 0x01, Mnemonic: "LS", Arguments: ""}
	CD        = Task{CommandId: 0x02, Mnemonic: "CD", Arguments: ""}
	PROCESSES = Task{CommandId: 0x03, Mnemonic: "PROCESSES", Arguments: ""}
	PWD       = Task{CommandId: 0x04, Mnemonic: "PWD", Arguments: ""}
)
