; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 @getArgCount()
  store i32 %1, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %2 = call ptr @malloc(i32 4)
  store i32 %i1, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

declare i32 @getArgCount()

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
