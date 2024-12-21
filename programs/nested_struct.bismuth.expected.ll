; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"program::A" = type { i32, i32, i32 }

define %Unit @program(ptr %0) {
entry:
  %a = alloca %"program::A", align 8
  %1 = alloca %"program::A", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = getelementptr %"program::A", ptr %1, i32 0, i32 0
  store i32 1, ptr %2, align 4
  %3 = getelementptr %"program::A", ptr %1, i32 0, i32 1
  store i32 2, ptr %3, align 4
  %4 = getelementptr %"program::A", ptr %1, i32 0, i32 2
  store i32 3, ptr %4, align 4
  %5 = load %"program::A", ptr %1, align 4
  store %"program::A" %5, ptr %a, align 4
  %6 = call ptr @malloc(i32 4)
  store i32 0, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
