; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@1 = private unnamed_addr constant [15 x i8] c"c.recv() = %s\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %c2 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @foo)
  store ptr %1, ptr %c2, align 8
  %2 = call ptr @malloc(i32 8)
  store ptr @0, ptr %2, align 8
  %3 = load ptr, ptr %c2, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 0, ptr %5, align 4
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  ret %Unit zeroinitializer
}

define %Unit @foo(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  %5 = call i32 (...) @printf(ptr @1, ptr %3)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @_Execute(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)
