#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/grpcpp.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>


int main(int argc, char **argv)
{
    std::cout << "gRPC version: " << grpc::Version() << "\n";

    int port = 0;
    grpc::AsyncGenericService generic_service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort("127.0.0.1:0", grpc::InsecureServerCredentials(), &port);
    builder.RegisterAsyncGenericService(&generic_service);
    std::unique_ptr<grpc::ServerCompletionQueue> queue = builder.AddCompletionQueue();
    std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
    if (!server || port == 0)
    {
        std::cerr << "failed to start server\n";
        return 1;
    }

    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(
        "127.0.0.1:" + std::to_string(port), grpc::InsecureChannelCredentials());
    const bool connected =
        channel->WaitForConnected(std::chrono::system_clock::now() + std::chrono::seconds(10));
    const grpc_connectivity_state state = channel->GetState(false);

    server->Shutdown();
    queue->Shutdown();
    void *tag = nullptr;
    bool ok = false;
    while (queue->Next(&tag, &ok))
    {
    }

    if (!connected || state != GRPC_CHANNEL_READY)
    {
        std::cerr << "channel did not connect to port " << port << " (state " << state << ")\n";
        return 1;
    }
    std::cout << "connected to in-process server on port " << port << "\n";
    return 0;
}
