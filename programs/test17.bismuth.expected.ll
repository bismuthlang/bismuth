; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %a1 = load i32, ptr %a, align 4
  store i32 %a1, ptr %b, align 4
  store i32 1, ptr %a, align 4
  %1 = sub nsw i32 0, 1
  %2 = call ptr @malloc(i32 4)
  store i32 %1, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
