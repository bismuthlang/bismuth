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
  %save_blk = alloca [5 x ptr], align 8
  %cast_arr = alloca [5 x i32], align 4
  %a = alloca [5 x i32], align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = getelementptr ptr, ptr %a, i32 0, i32 0
  store i32 1, ptr %1, align 4
  %2 = getelementptr ptr, ptr %a, i32 0, i32 1
  store i32 2, ptr %2, align 4
  %3 = getelementptr ptr, ptr %a, i32 0, i32 2
  store i32 3, ptr %3, align 4
  %4 = getelementptr ptr, ptr %a, i32 0, i32 3
  store i32 4, ptr %4, align 4
  %5 = getelementptr ptr, ptr %a, i32 0, i32 4
  store i32 5, ptr %5, align 4
  %6 = call ptr @malloc(i32 4)
  store i32 1, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  %a1 = load [5 x i32], ptr %a, align 4
  store [5 x i32] %a1, ptr %cast_arr, align 4
  store i32 0, ptr %idx, align 4
  store i32 5, ptr %len, align 4
  br label %loop-cond

loop-cond:                                        ; preds = %loop, %entry
  %9 = load i32, ptr %len, align 4
  %10 = load i32, ptr %idx, align 4
  %11 = icmp slt i32 %10, %9
  br i1 %11, label %loop, label %rest

loop:                                             ; preds = %loop-cond
  %12 = load i32, ptr %idx, align 4
  %13 = getelementptr ptr, ptr %save_blk, i32 0, i32 %12
  %14 = load i32, ptr %idx, align 4
  %15 = getelementptr ptr, ptr %cast_arr, i32 0, i32 %14
  %16 = load ptr, ptr %15, align 8
  %17 = call ptr @malloc(i32 8)
  store ptr %16, ptr %17, align 8
  store ptr %17, ptr %13, align 8
  %18 = load i32, ptr %idx, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, ptr %idx, align 4
  br label %loop-cond

rest:                                             ; preds = %loop-cond
  %20 = getelementptr ptr, ptr %save_blk, i32 0, i32 0
  %21 = load i32, ptr %len, align 4
  %22 = call ptr @_ArrayToChannel(ptr %20, i32 %21)
  store ptr %22, ptr %c2, align 8
  %23 = load ptr, ptr %c2, align 8
  %24 = call i1 @_ShouldLinearLoop(ptr %23)
  br i1 %24, label %loop2, label %rest4

loop2:                                            ; preds = %loop2, %rest
  %25 = load ptr, ptr %c2, align 8
  %26 = call ptr @_ReadLinearChannel(ptr %25)
  %27 = load i32, ptr %26, align 4
  %28 = call %Unit @free(ptr %26)
  store i32 %27, ptr %val, align 4
  %val3 = load i32, ptr %val, align 4
  %29 = call %Unit (ptr, ...) @printf(ptr @0, i32 %val3)
  %30 = load ptr, ptr %c2, align 8
  %31 = call i1 @_ShouldLinearLoop(ptr %30)
  br i1 %31, label %loop2, label %rest4

rest4:                                            ; preds = %loop2, %rest
  %32 = call %Unit (ptr, ...) @printf(ptr @1)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_ArrayToChannel(ptr, i32)

declare i1 @_ShouldLinearLoop(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)
