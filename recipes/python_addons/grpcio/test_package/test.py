import asyncio
import grpc


async def test_async_api():
    channel = grpc.aio.insecure_channel("localhost:50051")
    await channel.close()


def main():
    channel = grpc.insecure_channel("localhost:50051")
    assert channel is not None

    future = grpc.channel_ready_future(channel)
    future.cancel()

    assert hasattr(grpc, "aio")
    asyncio.run(test_async_api())

    print(f"grpcio smoke test passed with grpcio {grpc.__version__}")


if __name__ == "__main__":
    main()
