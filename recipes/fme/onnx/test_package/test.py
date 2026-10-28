import numpy

import onnx
from onnx import TensorProto, helper

inputs = [
    helper.make_tensor_value_info("x", TensorProto.FLOAT, [2]),
    helper.make_tensor_value_info("y", TensorProto.FLOAT, [2]),
]
outputs = [helper.make_tensor_value_info("z", TensorProto.FLOAT, [2])]
graph = helper.make_graph([helper.make_node("Add", ["x", "y"], ["z"])], "add", inputs, outputs)
model = helper.make_model(graph, opset_imports=[helper.make_opsetid("", 21)])

onnx.checker.check_model(model)
inferred = onnx.shape_inference.infer_shapes(model)
assert [d.dim_value for d in inferred.graph.output[0].type.tensor_type.shape.dim] == [2]

assert onnx.__version__ != "unknown"
print(f"onnx {onnx.__version__}, numpy {numpy.__version__}")
