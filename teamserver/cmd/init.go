// This file is mean to initialize the team core. Example: ./Amethyst -i 172.168.14.123 -p 8080 -pwd password123!
package cmd

import (
	"Amethyst/core"
	"fmt"
	"github.com/spf13/cobra"
	"os"
)

type State struct {
	SelectedAgent int
	CurrentView   string
}

var rootCmd = &cobra.Command{ //
	Use:   "./Amethyst -i <ip> -p <port>",
	Short: "",
	Long:  `Amethyst`,
	Run: func(cmd *cobra.Command, args []string) {
		// Main Function Here

	},
}

func Execute() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	t := core.InitializeTeamServer()

	/*
		// TODO THIS THIS JUST FOR TESTING WHILE BUILDING QT CLIENT
		newAgent := core.Agent{
			Id:             len(t.Agents) + 1,
			Listener:       "/default", // because using default ** change **
			ComputerName:   "test",
			UserName:       "WinDev",
			ExternalIp:     "43.431.43.131",
			InternalIp:     "192.169.420.69",
			WindowsVersion: "Windows 10",
			PID:            43153,
			ProcessName:    "agent.exe",
			Sleep:          10,
			LastCallHome:   0, // change this
			TaskQueue:      make([]*tasks.Task, 0),
		}
		// Add to agent
		t.Agents[len(t.Agents)+1] = &newAgent
	*/
	go t.Start()
	fmt.Println("Started Agent HTTP Listener Server on http://localhost:8081")

	fmt.Println("Started Operator Server on http://localhost:9998")
	t.InitializeWebSocketOperatorServer()
}
