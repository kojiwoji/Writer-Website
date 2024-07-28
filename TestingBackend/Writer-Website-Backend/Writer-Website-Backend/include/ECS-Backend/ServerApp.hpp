#ifndef SERVER_APP_HPP
#define SERVER_APP_HPP

#include<ECS-Backend/Keywords.hpp>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/ThreadPool.h>
#include <iostream>
#include <string>
#include <sstream>

/// ECS - Component
#include <ECS-Backend/Structure/data/ServerData.hpp>

/// ECS - System
#include <ECS-Backend/Structure/system/ServerStystemUpdate.hpp>


/// Class

class HelloRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override
    {
        response.setContentType("application/json");
        response.set("Access-Control-Allow-Origin", "*"); // Enable CORS
        response.set("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        response.set("Access-Control-Allow-Headers", "Content-Type");

        /// When the client tries to use 'get' we'll return the function.
        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.send();
            return;
        }

        try
        {
            // Read JSON from request body
            std::istream& requestStream = request.stream();
            std::ostringstream oss;
            oss << requestStream.rdbuf();
            std::string requestBody = oss.str();

            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(requestBody);
            Poco::JSON::Object::Ptr jsonObject = result.extract<Poco::JSON::Object::Ptr>();

            // Extract the "name" field from JSON
            std::string name = jsonObject->optValue<std::string>("name", "World");

            // Create JSON response
            Poco::JSON::Object responseObject;
            responseObject.set("message", "Hello, " + name + "!");

            std::ostream& responseStream = response.send();
            responseObject.stringify(responseStream, 2);
        }
        catch (const std::exception& e) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            std::ostream& responseStream = response.send();
            responseStream << "{\"error\": \"Invalid JSON format\"}";
        }
    }
};

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest&) override
    {
        return new HelloRequestHandler;
    }
};

class ServerApplication : public Poco::Util::ServerApplication
{
protected:
    int main(const std::vector<std::string>&) override
    {
        /*
        Poco::Net::ServerSocket svs(9080);
        Poco::Net::HTTPServer srv(new RequestHandlerFactory, svs, new Poco::Net::HTTPServerParams);

        srv.start();
        std::cout << "Server started" << std::endl;

        waitForTerminationRequest(); // Wait for CTRL-C or kill, Change this for checking a component.

        std::cout << "Shutting down..." << std::endl;
        srv.stop();
        */

        flecs::world server;

        /// Load all components.
        ECS_COMPONENT(server, ServerData);

        /// Initialize
        auto serverData = ServerEventInitalize(server);

        Poco::Net::ServerSocket svs(9080);
        Poco::Net::HTTPServer srv(new RequestHandlerFactory, svs, new Poco::Net::HTTPServerParams);
        
        /// Start Server
        srv.start();
        
        /// Start the Event system
        int i = 0;
        while (serverData.get<ServerData>()->state == ServerState::Activated)
        {
            if (i > 20)
            {
                int input;
                std::cout << "Event: ";
                std::cin >> input;

                if (input == 0)
                {
                    ServerEventSend(server, serverData, ServerEvents::SE_Terminate);
                }
            }
            ServerEventUpdate(server, serverData);
            i++;
        }

        /// End the server
        srv.stop();
        
        return Application::EXIT_OK;
    }
};

#endif // !SERVER_APP_HPP