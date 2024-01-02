#include "WebsocketServer.h"

#include <iostream>
#include <thread>
#include <asio/io_service.hpp>

// The port number the WebSocket server listens on
#define PORT_NUMBER 8181
#define REUSE_ADDR true

int main(int argc, char *argv[])
{
	// Create the event loop for the main thread, and the WebSocket server
	asio::io_service mainEventLoop;
	WebsocketServer server;

	// Register our network callbacks, ensuring the logic is run on the main thread's event loop
	server.connect([&mainEventLoop, &server](ClientConnection conn)
				   { mainEventLoop.post([conn, &server]()
										{
											std::clog << "Connection opened." << std::endl;
											std::clog << "There are now " << server.numConnections() << " open connections." << std::endl;

											// Send a hello message to the client
											//  server.sendMessage(conn, Json::Value());
										}); });
	server.disconnect([&mainEventLoop, &server](ClientConnection conn)
					  { mainEventLoop.post([conn, &server]()
										   {
			std::clog << "Connection closed." << std::endl;
			std::clog << "There are now " << server.numConnections() << " open connections." << std::endl; }); });
	server.message([&mainEventLoop, &server](ClientConnection conn, const Json::Value &args)
				   { mainEventLoop.post([conn, args, &server]()
										{
											std::clog << "message handler on the main thread" << std::endl;
											std::clog << "Message payload:" << std::endl;
											std::clog << server.stringifyJson(args) << std::endl;

											// Echo the message pack to the client
											// Validate that the incoming message contains valid JSON
											Json::Value messageObject = server.parseJson(server.stringifyJson(args));
											if (messageObject.isNull() == false)
											{
												server.broadcastMessage(messageObject);
											} }); });

	// Start the networking thread
	std::thread serverThread([&server]()
							 { server.run(PORT_NUMBER, REUSE_ADDR); });

	// Start the event loop for the main thread
	asio::io_service::work work(mainEventLoop);
	mainEventLoop.run();

	return 0;
}
