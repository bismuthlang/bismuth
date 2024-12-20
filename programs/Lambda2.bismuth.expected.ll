; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [9 x i8] c"FOO: %u\0A\00", align 1
@1 = private unnamed_addr constant [22 x i8] c"ref (:= foo(1)) = %u\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %i = alloca i32, align 4
  %t3 = alloca ptr, align 8
  %k = alloca i32, align 4
  %j = alloca i32, align 4
  %t2 = alloca ptr, align 8
  %t1 = alloca ptr, align 8
  %ref = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store ptr @"program::foo", ptr %ref, align 8
  %ref1 = load ptr, ptr %ref, align 8
  %1 = call ptr @_Execute(ptr %ref1)
  store ptr %1, ptr %t1, align 8
  %2 = call ptr @malloc(i32 4)
  store i32 10, ptr %2, align 4
  %3 = load ptr, ptr %t1, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @_Execute(ptr @"program::foo")
  store ptr %5, ptr %t2, align 8
  %6 = call ptr @malloc(i32 4)
  store i32 11, ptr %6, align 4
  %7 = load ptr, ptr %t2, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  %9 = load ptr, ptr %t1, align 8
  %10 = call ptr @_ReadLinearChannel(ptr %9)
  %11 = load i32, ptr %10, align 4
  %12 = call %Unit @free(ptr %10)
  store i32 %11, ptr %j, align 4
  %13 = load ptr, ptr %t2, align 8
  %14 = call ptr @_ReadLinearChannel(ptr %13)
  %15 = load i32, ptr %14, align 4
  %16 = call %Unit @free(ptr %14)
  store i32 %15, ptr %k, align 4
  %ref2 = load ptr, ptr %ref, align 8
  %17 = call ptr @_Execute(ptr %ref2)
  store ptr %17, ptr %t3, align 8
  %18 = call ptr @malloc(i32 4)
  store i32 1, ptr %18, align 4
  %19 = load ptr, ptr %t3, align 8
  %20 = call %Unit @_WriteChannel(ptr %19, ptr %18)
  %21 = load ptr, ptr %t3, align 8
  %22 = call ptr @_ReadLinearChannel(ptr %21)
  %23 = load i32, ptr %22, align 4
  %24 = call %Unit @free(ptr %22)
  store i32 %23, ptr %i, align 4
  %i3 = load i32, ptr %i, align 4
  %25 = call i32 (...) @printf(ptr @1, i32 %i3)
  %26 = call ptr @malloc(i32 4)
  store i32 0, ptr %26, align 4
  %27 = load ptr, ptr %c, align 8
  %28 = call %Unit @_WriteChannel(ptr %27, ptr %26)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

define private %Unit @"program::foo"(ptr %0) {
entry:
  %x = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  %5 = call i32 (...) @printf(ptr @0, i32 %x1)
  %x2 = load i32, ptr %x, align 4
  %6 = call ptr @malloc(i32 4)
  store i32 %x2, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
