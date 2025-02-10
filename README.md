<div align="center">

<h3 alt="The Bismuth Programming Language"><img src="https://bismuth-lang.org/logo2.svg" width="64" height="64"></h3>
<span align="center"><h3>The Bismuth Programming Language</h3></span> 
<h4 align="center"> Making it easier to write safe distributed & concurrent programs. </h4>

<span>[<a href="https://bismuth-lang.org/#editor">Online Editor</a>]</span> ·
<span>[<a href="https://docs.bismuth-lang.org/">Documentation</a>]</span> ·
<span>[<a href="https://docs.bismuth-lang.org/install.html">Installation & Contibuting</a>]</span>
</div>

---

### About

Writing programs for distributed and current systems is infamously challenging: most languages don't provide 
the tools to describe such systems—leaving programmers having to fill in the numerous edge cases left (and often concealed) by the language. 
Bismuth's goal is to bring such overlooked considerations into modern language design by exploring an implementing the most expressive yet easy to use abstractions for communicating such tasks. 
What sets Bismuth apart from other language's is its use of a [linear type system](https://en.wikipedia.org/wiki/Substructural_type_system#Linear_type_systems). This allows the language to capture how resources are used and interactions unfold over time; and then prove correctness properties about them. Practically, this means [deadlock freedom](https://bismuth-lang.org/ahf-CommunicatingProcessCalculus.pdf#subsubsection.7.3.1), [typed communications between processes](https://docs.bismuth-lang.org/ref/types.html#session-types), the [automatic detection of protocol violations](https://ahfriedman.com/projects/bismuth-session-protocol), and more.

### Example: Publish/Subscribe
Say that you want to implement a simple pub/sub system in Bismuth where clients can either: 
  - Publish messages to a topic
  - Stream messages from a set of topics

From the server's perspective, this communication be viewed as the following protocol: 
```
Cancelable<!( 
  ExternalChoice<
    publish: +u32;+str,
    stream: +u32[];Cancelable<?(-u32;-str)>
  >
)>
```
Breaking this down, the protocol first starts out by using a `Cancelable<...>` modality which specifies that the
protocol listed between the angled brackets can be canceled at any time by either party or due to a network failure. 
Within this cancelable block, we then use the "of course" operator, `!` to represent that the following protocol is 
repeated as many times as the remote program requests. In the context of our pubsub example, this represents that 
our server will serve client requests as long as the client has requests for the server to handle. What request 
can the client make? To capture this, we use an `ExternalChoice<...>` to provide the clients with the option to either 
follow the `publish` protocol or `stream` protocol. In the case of the former, the server will receive an unsigned 32-bit integer
from the client (representing the topic ID) followed by the string message the client wishes to publish to the topic.
In the case the client selects the `stream` protocol, the server first receives a dynamically sized array of topic IDs from 
the client to listen to messages on, and then enters into another `Cancelable<...>` block wherein we use the 
"why not" operator, `?` to allow the server to repeatedly send the client a `u32` topic ID followed by a string message from that topic. 

What's the cool part about all this? Bismuth captures concurrent communication through channels that are typed by session types, and 
Bismuth is able to ensure that all session types within a program are followed fully and completely in order to type check.
This means we don't need to worry about protocol violations—even in the case that we are using external networked communication, the 
Bismuth session protocol is able to automatically enforce such guarantees and handle data (de)serialization.

For example, we could write the program for a slightly more advanced pubsub system as follows:

```bismuth
struct ReqPublish {
    u32 topicId;
    str message;
}
struct ReqSubscribe {
    u32 topicId;
    u32 clientId;
}
struct ReqPull {
    u32 topicId;
    u32 clientId;
}

# ┌- Used to define a program; programs run concurrently and communicate via channels.
# | 
# |     ┌ The name of our program
# |     |
# |     |            ┌ The name of the channel within the program
# |     |            |
# |     |            |        ┌ The session type the channel follows
# v     v            v        v
prog pubsubServer :: io : Cancelable<   # Cancelable protocol as per above description
  !(
    ExternalChoice<
      publish: +ReqPublish, # Publish str to topic identified by u32
      subscribe: +ReqSubscribe,    # Subscribe to topic u32
      pull: +ReqPull;?-str # Stream messages we have subscribed to
    >
  )> {
  str[][][] topics;

  # Handle requests to the server as long as we are required
  accept(io) {
    offer io 
      | publish => {  # Handle the case our client requests to publish
            match io.recv()
                | Unit u => {} # Comms failed
                | ReqPublish req => 
            match topics[req.topicId]
                | Unit u => {} # Failed to allocate
                | str[][] topic => 
            for(u32 c := 0; c < topic.length; c := c + 1) {
                match topic[c] 
                    | Unit u => {} # Client is not subscribed
                    | str[] msgs => {
                        topic[c][msgs.length] := req.message;
                      }   
            }
        }
      | subscribe => { # Handle the client subscribing to a topic
          match io.recv()
            | Unit u => {} # Comms. Failed
            | ReqSubscribe req => {
                str[] msgs; 
                topics[req.topicId][req.clientId] := msgs; 
            }
        }
      | pull => {  # Send messages to the client
            match io.recv()
                | Unit u => {weaken(io)} # Comms failed
                | ReqPull req => {
            match topics[req.topicId]
                | Unit u => {weaken(io)} # Topic DNE
                | str[][] topic => {
            match topic[req.clientId] 
                | Unit u => {weaken(io)} # Client not subscribed
                | str[] msgs => { 
                    for(var i := 0; i < msgs.length; i := i + 1) {
                        match msgs[i]
                            | Unit u => {} # Impossible
                            | str msg => {
                                unfold(io)
                                io.send(msg);
                              }
                    }
                    weaken(io)
                  }}}
          }
      | else => {}
  }
  cancel(io)
}
``` 
*This README is currently being updated; see the sample programs on the project's [homepage](https://bismuth-lang.org/) as well as in the `./bsl`, `./programs`, and `./paper` directories of the repository.*


### Features
- Deadlock Freedom & Typed Communication between Processes via session types ([wikipedia](https://en.wikipedia.org/wiki/Session_type)|[docs](https://docs.bismuth-lang.org/ref/types.html#session-types))
  - First-class support for iteration in session types
  - A closeable/cancelable protocol modality which can be nested and located anywhere in the session as to account for anything from error handling to total communication failure
- Algebraic data types
- Garbage collection via [bdwgc](https://github.com/ivmai/bdwgc)
- Type inference


### Repository Structure

- `/antlr` - Contains the relevant ANTLR library.
- `/build` - Automatically generated output files of the project.
- `./coverage.sh` - Runs coverage based on the test cases
- `./cov` - Automatically generated folder containing coverage information
- `/cmake` - Contains the cmake files required to setup the project's dependencies. Each file corresponds to a separate part of the project.
- `/programs` - Contains sample programs used for testing the compiler.
- `/src` - Contains the main project files--including bismuthc.cpp which is the main entry point for the compiler
- `/src/codegen` - Code generation phase of the compiler
- `/src/generated` - Automatically generated ANTLR files based on the language's grammar
- `/src/lexparse` - The language's grammar 
- `/src/runtime` - The language's runtime library
- `/src/semantic` - The language's semantic analysis phase (type checking, type inference, etc).
- `/src/symbol` - Files related to the symbol table and type definitions
- `/src/utility` - Misc. files required for the compiler--primarily relating to test cases and error handling
- `./tester.sh` - Compiles and runs a given file
- `/test` - Compiler test cases primarily broken down based on corresponding file in `/src`.
- `./makeBuild.sh` - Makes a build of the project
- `./runTests.sh` - Runs the project's test cases
