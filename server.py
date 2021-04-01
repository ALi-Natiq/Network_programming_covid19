import zmq
context = zmq.Context()
try:
# Incoming messages come here
sink = context.socket(zmq.PULL)
sink.bind("tcp://*:5555") # in plaats van "tcp://*:24041"
# Outgoing message go out through here
publisher = context.socket(zmq.PUB)
publisher.bind("tcp://*:5556") # in plaats van "tcp://*:24024"
print("Server has started")
zmq.proxy(sink, publisher)
except zmq.ZMQError as ex:
print(ex)
