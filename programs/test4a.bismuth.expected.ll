; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [9 x i8] c"GOT: %d\0A\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"GOT: %d\0A\00", align 1
@2 = private unnamed_addr constant [9 x i8] c"GOT: %d\0A\00", align 1
@3 = private unnamed_addr constant [9 x i8] c"GOT: %d\0A\00", align 1
@4 = private unnamed_addr constant [9 x i8] c"ANS: %d\0A\00", align 1
@5 = private unnamed_addr constant [9 x i8] c"ANS: %d\0A\00", align 1

define %Unit @mutArgsOne(ptr %0) {
entry:
  %i = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %1 = load ptr, ptr %io, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %i, align 4
  %5 = icmp slt i32 5, 10
  %6 = xor i1 %5, true
  br i1 %6, label %then, label %else

then:                                             ; preds = %entry
  store i32 20, ptr %i, align 4
  br label %if-cont

else:                                             ; preds = %entry
  store i32 50, ptr %i, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %i1 = load i32, ptr %i, align 4
  %7 = call i32 (...) @printf(ptr @0, i32 %i1)
  %i2 = load i32, ptr %i, align 4
  %8 = call ptr @malloc(i32 4)
  store i32 %i2, ptr %8, align 4
  %9 = load ptr, ptr %io, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  ret %Unit zeroinitializer
}

define %Unit @mutArgsTwo(ptr %0) {
entry:
  %i = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %1 = load ptr, ptr %io, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %i, align 4
  %5 = icmp slt i32 5, 10
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  store i32 20, ptr %i, align 4
  br label %if-cont

else:                                             ; preds = %entry
  store i32 50, ptr %i, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %i1 = load i32, ptr %i, align 4
  %6 = call i32 (...) @printf(ptr @1, i32 %i1)
  %i2 = load i32, ptr %i, align 4
  %7 = call ptr @malloc(i32 4)
  store i32 %i2, ptr %7, align 4
  %8 = load ptr, ptr %io, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  ret %Unit zeroinitializer
}

define %Unit @PROCmutArgsOne(ptr %0) {
entry:
  %i = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %1 = load ptr, ptr %io, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %i, align 4
  %5 = icmp slt i32 5, 10
  %6 = xor i1 %5, true
  br i1 %6, label %then, label %else

then:                                             ; preds = %entry
  store i32 20, ptr %i, align 4
  br label %if-cont

else:                                             ; preds = %entry
  store i32 50, ptr %i, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %i1 = load i32, ptr %i, align 4
  %7 = call i32 (...) @printf(ptr @2, i32 %i1)
  ret %Unit zeroinitializer
}

define %Unit @PROCmutArgsTwo(ptr %0) {
entry:
  %i = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %1 = load ptr, ptr %io, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %i, align 4
  %5 = icmp slt i32 5, 10
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  store i32 20, ptr %i, align 4
  br label %if-cont

else:                                             ; preds = %entry
  store i32 50, ptr %i, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %i1 = load i32, ptr %i, align 4
  %6 = call i32 (...) @printf(ptr @3, i32 %i1)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %t6 = alloca i32, align 4
  %t5 = alloca i32, align 4
  %t4 = alloca ptr, align 8
  %t3 = alloca ptr, align 8
  %t2 = alloca ptr, align 8
  %t1 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @mutArgsOne)
  store ptr %1, ptr %t1, align 8
  %2 = call ptr @_Execute(ptr @mutArgsTwo)
  store ptr %2, ptr %t2, align 8
  %3 = call ptr @_Execute(ptr @PROCmutArgsOne)
  store ptr %3, ptr %t3, align 8
  %4 = call ptr @_Execute(ptr @PROCmutArgsTwo)
  store ptr %4, ptr %t4, align 8
  %5 = call ptr @malloc(i32 4)
  store i32 0, ptr %5, align 4
  %6 = load ptr, ptr %t1, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = call ptr @malloc(i32 4)
  store i32 0, ptr %8, align 4
  %9 = load ptr, ptr %t2, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = call ptr @malloc(i32 4)
  store i32 0, ptr %11, align 4
  %12 = load ptr, ptr %t3, align 8
  %13 = call %Unit @_WriteChannel(ptr %12, ptr %11)
  %14 = call ptr @malloc(i32 4)
  store i32 0, ptr %14, align 4
  %15 = load ptr, ptr %t4, align 8
  %16 = call %Unit @_WriteChannel(ptr %15, ptr %14)
  %17 = load ptr, ptr %t1, align 8
  %18 = call ptr @_ReadLinearChannel(ptr %17)
  %19 = load i32, ptr %18, align 4
  %20 = call %Unit @free(ptr %18)
  store i32 %19, ptr %t5, align 4
  %21 = load ptr, ptr %t2, align 8
  %22 = call ptr @_ReadLinearChannel(ptr %21)
  %23 = load i32, ptr %22, align 4
  %24 = call %Unit @free(ptr %22)
  store i32 %23, ptr %t6, align 4
  %t51 = load i32, ptr %t5, align 4
  %25 = call i32 (...) @printf(ptr @4, i32 %t51)
  %t62 = load i32, ptr %t6, align 4
  %26 = call i32 (...) @printf(ptr @5, i32 %t62)
  %27 = sub nsw i32 0, 1
  %28 = call ptr @malloc(i32 4)
  store i32 %27, ptr %28, align 4
  %29 = load ptr, ptr %c, align 8
  %30 = call %Unit @_WriteChannel(ptr %29, ptr %28)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
