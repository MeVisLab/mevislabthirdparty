import sys
from triton_protos import grpc_service_pb2
from triton_protos import grpc_service_pb2_grpc
from triton_protos import model_config_pb2


def main():
    if grpc_service_pb2.ModelInferRequest.DESCRIPTOR.full_name != "inference.ModelInferRequest":
        sys.exit(1)

    if model_config_pb2.DataType.DESCRIPTOR.full_name != "inference.DataType":
        sys.exit(2)

    if grpc_service_pb2_grpc.GRPCInferenceServiceStub is None:
        sys.exit(3)

    print("triton_protos imports ok")


if __name__ == "__main__":
    main()
