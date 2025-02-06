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

### Examples
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
