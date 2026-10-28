import numpy

import onnxruntime
from onnx import TensorProto, helper

inputs = [
    helper.make_tensor_value_info("x", TensorProto.FLOAT, [2]),
    helper.make_tensor_value_info("y", TensorProto.FLOAT, [2]),
]
outputs = [helper.make_tensor_value_info("z", TensorProto.FLOAT, [2])]
graph = helper.make_graph([helper.make_node("Add", ["x", "y"], ["z"])], "add", inputs, outputs)
model = helper.make_model(graph, opset_imports=[helper.make_opsetid("", 21)])

session = onnxruntime.InferenceSession(model.SerializeToString(), providers=["CPUExecutionProvider"])
(result,) = session.run(
    None,
    {"x": numpy.array([1, 2], dtype=numpy.float32), "y": numpy.array([3, 4], dtype=numpy.float32)},
)
assert result.tolist() == [4.0, 6.0]

print(f"onnxruntime {onnxruntime.__version__}, providers {onnxruntime.get_available_providers()}")
