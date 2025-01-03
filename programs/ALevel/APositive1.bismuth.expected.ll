; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %i = alloca i32, align 4
  %x = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 42, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  store i32 %i1, ptr %x, align 4
  %x2 = load i32, ptr %x, align 4
  %1 = call ptr @malloc(i32 4)
  store i32 %x2, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
