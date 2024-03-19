#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/log_stdout.h>

#include <signal.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>

#include "../include/json.hpp"

using json = nlohmann::json;

UA_Boolean running = true;

static void stopHandler(int sign)
{
    running = 0;
}

std::string ReadConfig() // Считываем файл конфигурации
{
    std::ifstream f("../configs/client_test.json");
    std::string opc = "opc.tcp://";

    json data = json::parse(f);
    json object = data["settings"];
    std::string address = object[0]["ip"];
    int port = object[0]["port"];

    opc += address;
    opc += ":";
    opc += std::to_string(port);
    return opc;
}

int main()
{
    signal(SIGINT, stopHandler);
    std::string opc = ReadConfig();

    UA_Client *client = UA_Client_new();
    UA_ClientConfig *cc = UA_Client_getConfig(client); // Создание клиента
    UA_ClientConfig_setDefault(cc);

    cc->timeout = 1000;

    UA_StatusCode retval;
    UA_Variant value;
    UA_Variant_init(&value);
    bool one = true;

    while (running)
    {
        retval = UA_Client_connectUsername(client, opc.c_str(), "paula", "paula123");
        if (retval == UA_STATUSCODE_BADCONNECTIONCLOSED)
        {
            continue;
        }
        if (retval != UA_STATUSCODE_GOOD)
        {
            UA_sleep_ms(1000);
            continue;
        }
        UA_BrowseRequest request;
        UA_BrowseRequest_init(&request);
        request.nodesToBrowse = UA_BrowseDescription_new();
        request.nodesToBrowseSize = 1;
        request.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER); // Идентификатор корневой папки объектов сервера
        request.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL;                  // Запрашиваем все возможные результаты
        UA_BrowseResponse response = UA_Client_Service_browse(client, request);

        if (one)
        {
            one = false;
            UA_Int32 myVariableValue = 42;
            UA_VariableAttributes myVariableAttributes = UA_VariableAttributes_default;
            myVariableAttributes.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
            myVariableAttributes.displayName = UA_LOCALIZEDTEXT("en-US", "My Variable");
            myVariableAttributes.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
            myVariableAttributes.valueRank = -1;

            UA_NodeId variableNodeId = UA_NODEID_NULL;
            UA_StatusCode retval = UA_Client_addVariableNode(client, variableNodeId,
                                                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                                             UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                                                             UA_QUALIFIEDNAME(1, "my_variable"),
                                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                             myVariableAttributes, &variableNodeId);
        }
        // Обработка ответа и чтение значений переменных
        for (size_t i = 0; i < response.resultsSize; ++i)
        {
            json data_value;
            int count = 0;
            for (size_t j = 0; j < response.results[i].referencesSize; ++j)
            {
                UA_ReferenceDescription *ref = &(response.results[i].references[j]);
                if (ref->nodeClass != UA_NODECLASS_VARIABLE)
                {
                    continue; // Пропускаем узлы, которые не являются переменными
                }

                UA_NodeId nodeId = ref->nodeId.nodeId;

                UA_ReadRequest readRequest;
                UA_ReadRequest_init(&readRequest);
                readRequest.nodesToRead = UA_ReadValueId_new();
                readRequest.nodesToReadSize = 1;
                readRequest.nodesToRead[0].nodeId = nodeId;
                readRequest.nodesToRead[0].attributeId = UA_ATTRIBUTEID_VALUE;
                UA_ReadResponse readResponse = UA_Client_Service_read(client, readRequest);

                if (readResponse.responseHeader.serviceResult == UA_STATUSCODE_GOOD && readResponse.resultsSize > 0 && readResponse.results[0].hasValue)
                {
                    UA_Variant value = readResponse.results[0].value;
                    char *name = (char *)UA_malloc(sizeof(char) * ref->displayName.text.length + 1);
                    memccpy(name, ref->displayName.text.data, 0, ref->displayName.text.length);
                    data_value[count]["name"] = name;

                    // Обработка значения переменной
                    if (value.type == &UA_TYPES[UA_TYPES_INT32])
                    {
                        UA_Variant newValue;
                        UA_Variant_init(&newValue);
                        UA_Int32 raw_date = *(UA_Int32 *)value.data;
                        data_value[count]["value"] = raw_date;
                        raw_date += 1;
                        UA_Variant_setScalar(&newValue, &raw_date, &UA_TYPES[UA_TYPES_INT32]);
                        retval = UA_Client_writeValueAttribute(client, nodeId, &newValue);
                    }
                    if (value.type == &UA_TYPES[UA_TYPES_DOUBLE])
                    {
                        UA_Double raw_date = *(UA_Double *)value.data;
                        data_value[count]["value"] = raw_date;
                    }
                    count++;
                }
            }
            std::string s = data_value.dump();
            std::cout << s << std::endl;

        }
        UA_sleep_ms(1000);
    };

    UA_Variant_clear(&value);
    UA_Client_delete(client);
    return EXIT_SUCCESS;
}
