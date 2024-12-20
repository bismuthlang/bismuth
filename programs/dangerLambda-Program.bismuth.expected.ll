; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [9 x i8] c"Main 1!\0A\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"Main 2!\0A\00", align 1

define %Unit @getMain1(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 8)
  store ptr @"getMain1::main", ptr %1, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define %Unit @getMain2(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 8)
  store ptr @"getMain2::main", ptr %1, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %i2 = alloca i32, align 4
  %i1 = alloca i32, align 4
  %c2a = alloca ptr, align 8
  %c1a = alloca ptr, align 8
  %m2 = alloca ptr, align 8
  %m1 = alloca ptr, align 8
  %c2 = alloca ptr, align 8
  %c1 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @getMain1)
  store ptr %1, ptr %c1, align 8
  %2 = call ptr @_Execute(ptr @getMain2)
  store ptr %2, ptr %c2, align 8
  %3 = load ptr, ptr %c1, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load ptr, ptr %4, align 8
  %6 = call %Unit @free(ptr %4)
  store ptr %5, ptr %m1, align 8
  %7 = load ptr, ptr %c2, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load ptr, ptr %8, align 8
  %10 = call %Unit @free(ptr %8)
  store ptr %9, ptr %m2, align 8
  %m11 = load ptr, ptr %m1, align 8
  %11 = call ptr @_Execute(ptr %m11)
  store ptr %11, ptr %c1a, align 8
  %m22 = load ptr, ptr %m2, align 8
  %12 = call ptr @_Execute(ptr %m22)
  store ptr %12, ptr %c2a, align 8
  %13 = load ptr, ptr %c1a, align 8
  %14 = call ptr @_ReadLinearChannel(ptr %13)
  %15 = load i32, ptr %14, align 4
  %16 = call %Unit @free(ptr %14)
  store i32 %15, ptr %i1, align 4
  %17 = load ptr, ptr %c2a, align 8
  %18 = call ptr @_ReadLinearChannel(ptr %17)
  %19 = load i32, ptr %18, align 4
  %20 = call %Unit @free(ptr %18)
  store i32 %19, ptr %i2, align 4
  %i13 = load i32, ptr %i1, align 4
  %i24 = load i32, ptr %i2, align 4
  %21 = add nsw i32 %i13, %i24
  %22 = call ptr @malloc(i32 4)
  store i32 %21, ptr %22, align 4
  %23 = load ptr, ptr %c, align 8
  %24 = call %Unit @_WriteChannel(ptr %23, ptr %22)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private %Unit @"getMain1::main"(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 (ptr, ...) @printf(ptr @0)
  %2 = call ptr @malloc(i32 4)
  store i32 0, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

define private %Unit @"getMain2::main"(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 (ptr, ...) @printf(ptr @1)
  %2 = call ptr @malloc(i32 4)
  store i32 0, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  ret %Unit zeroinitializer
}

declare ptr @_Execute(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)
