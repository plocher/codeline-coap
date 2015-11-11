# codeline-coap
Model Railroad Control Point codeline - implemented on Particle's CoAP pub/sub event framework

A codeline message is an 8-byte array of bits, with each bit representing some part of the field appliance,
such as a Maintainer Call light, a Switch-Normal or Signal-at-Stop indication.

Codelines carry control and indication messages, 
* controls usually are from a dispatcher to a particular field unit, while 
* indications are from a field unit back to the dispatcher.

CoAP2code() converts an event into a codeline message
publishControls() and publishIndications() convert codeline messages into events

