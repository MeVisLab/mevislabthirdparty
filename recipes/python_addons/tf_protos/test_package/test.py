import sys
from tf_protos.tensorflow.core.framework import tensor_pb2
from tf_protos.tensorflow_serving.apis import get_model_metadata_pb2
from tf_protos.tensorflow_serving.apis import model_service_pb2_grpc
from tf_protos.tensorflow_serving.apis import predict_pb2
from tf_protos.tensorflow_serving.apis import prediction_service_pb2_grpc


def main():
    if tensor_pb2.TensorProto.DESCRIPTOR.full_name != "tensorflow.TensorProto":
        sys.exit(1)
    if predict_pb2.PredictRequest.DESCRIPTOR.full_name != "tensorflow.serving.PredictRequest":
        sys.exit(2)
    if get_model_metadata_pb2.GetModelMetadataRequest.DESCRIPTOR.full_name != (
        "tensorflow.serving.GetModelMetadataRequest"
    ):
        sys.exit(3)
    if model_service_pb2_grpc.ModelServiceStub is None:
        sys.exit(4)
    if prediction_service_pb2_grpc.PredictionServiceStub is None:
        sys.exit(5)
    print("tf_protos imports ok")


if __name__ == "__main__":
    main()
