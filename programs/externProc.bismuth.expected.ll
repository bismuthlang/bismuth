; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %current = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 1, ptr %current, align 4
  %1 = sub nsw i32 0, 1
  %2 = call ptr @malloc(i32 4)
  store i32 %1, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

declare %Unit @foo(i32, i32)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)