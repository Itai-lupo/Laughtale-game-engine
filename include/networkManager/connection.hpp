#pragma once
#include "core.hpp"
#include "packet.hpp"
#include "networkInterface.hpp"
#include <string>
#include <thread>
#include "dataFormatter.hpp"
#include "dataCryptographer.hpp"
#include <functional>
#include "mouseMoveData.hpp"

namespace LTE::GMNM
{
    // struct connectionData: public coreEventData
    // {
    //     connectionId conId;
    //     std::string ip;
    //     uint32_t port;
    //     std::function<void(packet& data)> send;

    //    connectionData(connectionId conId, const std::string& ip, uint32_t port, std::function<void(packet& data)> send): 
    //     conId(conId), ip(ip), port(port), send(send){}
    // };

    // struct connectionReadData: public connectionData
    // {
    //     packet data;

    //    connectionReadData(packet data, connectionId conId, const std::string& ip, uint32_t port, std::function<void(packet& data)> send): 
    //     connectionData(conId, ip, port, send), data(data){}
    // };
    
    class connection
    {
        private:
            bool canSend = false;
            connectionId id = 0;
            std::thread *listeningThread;
            networkInterface *networkConnction;
            dataFormatter *messageFormat;
            dataCryptographer *dataEncryption;
            bool shouldListen = true;
            
            void connect();
            void listen();

            std::string ip;
            uint32_t port;

        public:
            connection(const std::string& ip, uint32_t port, dataFormatter *messageFormat, dataCryptographer *dataEncryption);
            ~connection();

            connectionId getId(){ return id; }
            void fullClose(){ networkConnction->fullClose(); }

            void send(packet& data);
    };    
}