import zmq

assert isinstance(zmq.zmq_version_info(), tuple)
assert zmq.has("curve")

context = zmq.Context()
server = context.socket(zmq.PAIR)
client = context.socket(zmq.PAIR)
server.setsockopt(zmq.RCVTIMEO, 5000)
client.setsockopt(zmq.RCVTIMEO, 5000)
server.bind("inproc://test_package")
client.connect("inproc://test_package")

client.send(b"ping")
assert server.recv() == b"ping"
server.send_string("pong")
assert client.recv_string() == "pong"

client.close()
server.close()
context.term()
