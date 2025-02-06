; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %c1 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @"foo<int>")
  store ptr %1, ptr %c1, align 8
  %2 = call ptr @malloc(i32 4)
  store i32 5, ptr %2, align 4
  %3 = load ptr, ptr %c1, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = load ptr, ptr %c1, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load i32, ptr %6, align 4
  %8 = call %Unit @free(ptr %6)
  %9 = call %Unit (ptr, ...) @printf(ptr @0, i32 %7)
  %10 = call ptr @malloc(i32 4)
  store i32 0, ptr %10, align 4
  %11 = load ptr, ptr %c, align 8
  %12 = call %Unit @_WriteChannel(ptr %11, ptr %10)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

define %Unit @"foo<int>"(ptr %0) {
entry:
  %t = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %t, align 4
  %t1 = load i32, ptr %t, align 4
  %5 = call ptr @malloc(i32 4)
  store i32 %t1, ptr %5, align 4
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  ret %Unit zeroinitializer
}

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
