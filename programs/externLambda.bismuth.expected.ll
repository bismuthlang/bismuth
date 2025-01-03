; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [8 x i8] c"Hello \0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store ptr @printf, ptr %a, align 8
  %a1 = load ptr, ptr %a, align 8
  %1 = call i32 (ptr, ...) %a1(ptr @0)
  %2 = call ptr @malloc(i32 4)
  store i32 0, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
