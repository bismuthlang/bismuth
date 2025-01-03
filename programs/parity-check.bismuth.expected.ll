; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%Empty = type {}
%IntBox = type { i32 }

@0 = private unnamed_addr constant [23 x i8] c"prog1: ib.number = %u\0A\00", align 1
@1 = private unnamed_addr constant [22 x i8] c"prog1: sending ib...\0A\00", align 1
@2 = private unnamed_addr constant [21 x i8] c"prog1: recvd signal\0A\00", align 1
@3 = private unnamed_addr constant [23 x i8] c"prog1: ib.number = %u\0A\00", align 1
@4 = private unnamed_addr constant [21 x i8] c"prog2: recvd IntBox\0A\00", align 1
@5 = private unnamed_addr constant [23 x i8] c"prog2: ib.number = %u\0A\00", align 1
@6 = private unnamed_addr constant [23 x i8] c"prog2: ib.number = %u\0A\00", align 1
@7 = private unnamed_addr constant [26 x i8] c"prog2: sending signal...\0A\00", align 1

define %Unit @prog1(ptr %0) {
entry:
  %sig = alloca %Empty, align 8
  %ib = alloca %IntBox, align 8
  %1 = alloca %IntBox, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = getelementptr %IntBox, ptr %1, i32 0, i32 0
  store i32 15, ptr %2, align 4
  %3 = load %IntBox, ptr %1, align 4
  store %IntBox %3, ptr %ib, align 4
  %4 = getelementptr %IntBox, ptr %ib, i32 0, i32 0
  %5 = load i32, ptr %4, align 4
  %6 = call i32 (ptr, ...) @printf(ptr @0, i32 %5)
  %7 = call i32 (ptr, ...) @printf(ptr @1)
  %ib1 = load %IntBox, ptr %ib, align 4
  %8 = call ptr @malloc(i32 4)
  store %IntBox %ib1, ptr %8, align 4
  %9 = load ptr, ptr %c, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = load ptr, ptr %c, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load %Empty, ptr %12, align 1
  %14 = call %Unit @free(ptr %12)
  store %Empty %13, ptr %sig, align 1
  %15 = call i32 (ptr, ...) @printf(ptr @2)
  %16 = getelementptr %IntBox, ptr %ib, i32 0, i32 0
  %17 = load i32, ptr %16, align 4
  %18 = call i32 (ptr, ...) @printf(ptr @3, i32 %17)
  ret %Unit zeroinitializer
}

define %Unit @prog2(ptr %0) {
entry:
  %1 = alloca %Empty, align 8
  %ib = alloca %IntBox, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call ptr @_ReadLinearChannel(ptr %2)
  %4 = load %IntBox, ptr %3, align 4
  %5 = call %Unit @free(ptr %3)
  store %IntBox %4, ptr %ib, align 4
  %6 = call i32 (ptr, ...) @printf(ptr @4)
  %7 = getelementptr %IntBox, ptr %ib, i32 0, i32 0
  %8 = load i32, ptr %7, align 4
  %9 = call i32 (ptr, ...) @printf(ptr @5, i32 %8)
  %10 = getelementptr %IntBox, ptr %ib, i32 0, i32 0
  store i32 20, ptr %10, align 4
  %11 = getelementptr %IntBox, ptr %ib, i32 0, i32 0
  %12 = load i32, ptr %11, align 4
  %13 = call i32 (ptr, ...) @printf(ptr @6, i32 %12)
  %14 = call i32 (ptr, ...) @printf(ptr @7)
  %15 = load %Empty, ptr %1, align 1
  %16 = call ptr @malloc(i32 0)
  store %Empty %15, ptr %16, align 1
  %17 = load ptr, ptr %c, align 8
  %18 = call %Unit @_WriteChannel(ptr %17, ptr %16)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %temp2 = alloca %Empty, align 8
  %temp = alloca %IntBox, align 8
  %p2 = alloca ptr, align 8
  %p1 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @prog1)
  store ptr %1, ptr %p1, align 8
  %2 = call ptr @_Execute(ptr @prog2)
  store ptr %2, ptr %p2, align 8
  %3 = load ptr, ptr %p1, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load %IntBox, ptr %4, align 4
  %6 = call %Unit @free(ptr %4)
  store %IntBox %5, ptr %temp, align 4
  %temp1 = load %IntBox, ptr %temp, align 4
  %7 = call ptr @malloc(i32 4)
  store %IntBox %temp1, ptr %7, align 4
  %8 = load ptr, ptr %p2, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  %10 = load ptr, ptr %p2, align 8
  %11 = call ptr @_ReadLinearChannel(ptr %10)
  %12 = load %Empty, ptr %11, align 1
  %13 = call %Unit @free(ptr %11)
  store %Empty %12, ptr %temp2, align 1
  %temp22 = load %Empty, ptr %temp2, align 1
  %14 = call ptr @malloc(i32 0)
  store %Empty %temp22, ptr %14, align 1
  %15 = load ptr, ptr %p1, align 8
  %16 = call %Unit @_WriteChannel(ptr %15, ptr %14)
  %17 = sub nsw i32 0, 1
  %18 = call ptr @malloc(i32 4)
  store i32 %17, ptr %18, align 4
  %19 = load ptr, ptr %c, align 8
  %20 = call %Unit @_WriteChannel(ptr %19, ptr %18)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @_Execute(ptr)
