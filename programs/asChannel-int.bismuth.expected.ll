; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [4 x i8] c"%u \00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %val = alloca i32, align 4
  %c2 = alloca ptr, align 8
  %len = alloca i32, align 4
  %idx = alloca i32, align 4
  %save_blk = alloca [1 x ptr], align 8
  %createdArray = alloca [1 x i32], align 4
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 5, ptr %a, align 4
  %1 = call ptr @malloc(i32 4)
  store i32 1, ptr %1, align 4
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  %a1 = load i32, ptr %a, align 4
  %4 = getelementptr [1 x i32], ptr %createdArray, i32 0, i32 0
  store i32 %a1, ptr %4, align 4
  store i32 0, ptr %idx, align 4
  store i32 1, ptr %len, align 4
  br label %loop-cond

loop-cond:                                        ; preds = %loop, %entry
  %5 = load i32, ptr %len, align 4
  %6 = load i32, ptr %idx, align 4
  %7 = icmp slt i32 %6, %5
  br i1 %7, label %loop, label %rest

loop:                                             ; preds = %loop-cond
  %8 = load i32, ptr %idx, align 4
  %9 = getelementptr [1 x ptr], ptr %save_blk, i32 0, i32 %8
  %10 = load i32, ptr %idx, align 4
  %11 = getelementptr [1 x i32], ptr %createdArray, i32 0, i32 %10
  %12 = load i32, ptr %11, align 4
  %13 = call ptr @malloc(i32 4)
  store i32 %12, ptr %13, align 4
  store ptr %13, ptr %9, align 8
  %14 = load i32, ptr %idx, align 4
  %15 = add nsw i32 %14, 1
  store i32 %15, ptr %idx, align 4
  br label %loop-cond

rest:                                             ; preds = %loop-cond
  %16 = getelementptr [1 x ptr], ptr %save_blk, i32 0, i32 0
  %17 = load i32, ptr %len, align 4
  %18 = call ptr @_ArrayToChannel(ptr %16, i32 %17)
  store ptr %18, ptr %c2, align 8
  %19 = load ptr, ptr %c2, align 8
  %20 = call i1 @_ShouldLinearLoop(ptr %19)
  br i1 %20, label %loop2, label %rest4

loop2:                                            ; preds = %loop2, %rest
  %21 = load ptr, ptr %c2, align 8
  %22 = call ptr @_ReadLinearChannel(ptr %21)
  %23 = load i32, ptr %22, align 4
  %24 = call %Unit @free(ptr %22)
  store i32 %23, ptr %val, align 4
  %val3 = load i32, ptr %val, align 4
  %25 = call %Unit (ptr, ...) @printf(ptr @0, i32 %val3)
  %26 = load ptr, ptr %c2, align 8
  %27 = call i1 @_ShouldLinearLoop(ptr %26)
  br i1 %27, label %loop2, label %rest4

rest4:                                            ; preds = %loop2, %rest
  %28 = call %Unit (ptr, ...) @printf(ptr @1)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_ArrayToChannel(ptr, i32)

declare i1 @_ShouldLinearLoop(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)
