#include <iostream>

#include <igtlCapabilityMessage.h>
#include <igtlServerSocket.h>

int main()
{
    igtl::CapabilityMessage::Pointer capabilityMsg;
    capabilityMsg = igtl::CapabilityMessage::New();
    capabilityMsg->SetDeviceName("Device");

    igtl::ServerSocket::Pointer serverSocket;
    serverSocket = igtl::ServerSocket::New();

    return 0;
}
