#pragma once
#include "core.hpp"
#include "networkInterface.hpp"
#include <string>
#include <thread>
#include <vector>
#include "packet.hpp"
#include "connection.hpp"

namespace LTE::GMNM
{
    class connectionsManager
    {
        private:
            static std::vector<connection*> *connections;
            

        public:
            static void init();
            static void close();

            static connectionId addConnection(const std::string& ip, uint32_t port, dataFormatter *messageFormat, dataCryptographer *dataEncryption = new noEncrption());
            static void removeConnection(connectionId id);
            static connection *getConnection(connectionId id);
            
            static void sendData(connectionId id, packet& data);
    };    
}