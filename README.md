# HPXDistributed

Simplified implementation of the event processing model used within Athena using HPX for parallel and distributed processing.

In this implementation, each event is the unit of work which gets offloaded to a locality by the global scheduler to a worker component.
The processing of a single event is a DAG of algorithms with dataflow dependencies only. This DAG is the same for each event and the dependency tree is defined 
at build time. It is possible to request which algorithm to execute for a given event and only execute those and their (transitive) dependencies.

A global scheduler is instantiated on a single locality at launch. It will create a HPX component on each locality and schedule events on each worker component in a round-robin fashion. A future is returned to wait on the execution and retrieve the output.

When a worker component is instantiated, it will create an instance of each algorithm in the DAG. The same algorithm instance is used for each event so the ```operator()``` method of a given algorithm implementation should be reentrant. Whenever an event is sent to a worker, it walks up the dependencies tree and creates the future graph which gets offloaded to HPX. When every algorithm within an event has been scheduled, the server components wait until all the algorithms are done and then returns the event context. The processing of an event is kept within one locality.

Algorithms within an event read / write data using a blackboard model, the event context. Each event has its own event context instance. The event context must be thread-safe as we have intra-event parallelism. Within the current implementation, algorithms are passed an event context as an argument to the ```operator()``` but it is not currently used, algorithms are only CPU cruncher doing floating-point operations.