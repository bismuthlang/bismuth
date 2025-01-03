; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%Empty = type {}
%IntBoxBox = type { %IntBox }
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
  %ib = alloca %IntBoxBox, align 8
  %1 = alloca %IntBoxBox, align 8
  %2 = alloca %IntBox, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = getelementptr %IntBox, ptr %2, i32 0, i32 0
  store i32 15, ptr %3, align 4
  %4 = load %IntBox, ptr %2, align 4
  %5 = getelementptr %IntBoxBox, ptr %1, i32 0, i32 0
  store %IntBox %4, ptr %5, align 4
  %6 = load %IntBoxBox, ptr %1, align 4
  store %IntBoxBox %6, ptr %ib, align 4
  %7 = getelementptr %IntBoxBox, ptr %ib, i32 0, i32 0, i32 0
  %8 = load i32, ptr %7, align 4
  %9 = call i32 (ptr, ...) @printf(ptr @0, i32 %8)
  %10 = call i32 (ptr, ...) @printf(ptr @1)
  %ib1 = load %IntBoxBox, ptr %ib, align 4
  %11 = call ptr @malloc(i32 4)
  store %IntBoxBox %ib1, ptr %11, align 4
  %12 = load ptr, ptr %c, align 8
  %13 = call %Unit @_WriteChannel(ptr %12, ptr %11)
  %14 = load ptr, ptr %c, align 8
  %15 = call ptr @_ReadLinearChannel(ptr %14)
  %16 = load %Empty, ptr %15, align 1
  %17 = call %Unit @free(ptr %15)
  store %Empty %16, ptr %sig, align 1
  %18 = call i32 (ptr, ...) @printf(ptr @2)
  %19 = getelementptr %IntBoxBox, ptr %ib, i32 0, i32 0, i32 0
  %20 = load i32, ptr %19, align 4
  %21 = call i32 (ptr, ...) @printf(ptr @3, i32 %20)
  ret %Unit zeroinitializer
}

define %Unit @prog2(ptr %0) {
entry:
  %1 = alloca %Empty, align 8
  %2 = alloca %IntBox, align 8
  %ib = alloca %IntBoxBox, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = load ptr, ptr %c, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load %IntBoxBox, ptr %4, align 4
  %6 = call %Unit @free(ptr %4)
  store %IntBoxBox %5, ptr %ib, align 4
  %7 = call i32 (ptr, ...) @printf(ptr @4)
  %8 = getelementptr %IntBoxBox, ptr %ib, i32 0, i32 0, i32 0
  %9 = load i32, ptr %8, align 4
  %10 = call i32 (ptr, ...) @printf(ptr @5, i32 %9)
  %11 = getelementptr %IntBoxBox, ptr %ib, i32 0, i32 0
  %12 = getelementptr %IntBox, ptr %2, i32 0, i32 0
  store i32 20, ptr %12, align 4
  %13 = load %IntBox, ptr %2, align 4
  store %IntBox %13, ptr %11, align 4
  %14 = getelementptr %IntBoxBox, ptr %ib, i32 0, i32 0, i32 0
  %15 = load i32, ptr %14, align 4
  %16 = call i32 (ptr, ...) @printf(ptr @6, i32 %15)
  %17 = call i32 (ptr, ...) @printf(ptr @7)
  %18 = load %Empty, ptr %1, align 1
  %19 = call ptr @malloc(i32 0)
  store %Empty %18, ptr %19, align 1
  %20 = load ptr, ptr %c, align 8
  %21 = call %Unit @_WriteChannel(ptr %20, ptr %19)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %temp2 = alloca %Empty, align 8
  %temp = alloca %IntBoxBox, align 8
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
  %5 = load %IntBoxBox, ptr %4, align 4
  %6 = call %Unit @free(ptr %4)
  store %IntBoxBox %5, ptr %temp, align 4
  %temp1 = load %IntBoxBox, ptr %temp, align 4
  %7 = call ptr @malloc(i32 4)
  store %IntBoxBox %temp1, ptr %7, align 4
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
