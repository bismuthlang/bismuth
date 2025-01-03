; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %val = alloca ptr, align 8
  %c2 = alloca ptr, align 8
  %len = alloca i32, align 4
  %idx = alloca i32, align 4
  %save_blk = alloca [1 x ptr], align 8
  %createdArray = alloca [1 x ptr], align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %c1 = load ptr, ptr %c, align 8
  %1 = getelementptr [1 x ptr], ptr %createdArray, i32 0, i32 0
  store ptr %c1, ptr %1, align 8
  store i32 0, ptr %idx, align 4
  store i32 1, ptr %len, align 4
  br label %loop-cond

loop-cond:                                        ; preds = %loop, %entry
  %2 = load i32, ptr %idx, align 4
  %3 = load i32, ptr %len, align 4
  %4 = icmp slt i32 %2, %3
  br i1 %4, label %loop, label %rest

loop:                                             ; preds = %loop-cond
  %5 = load i32, ptr %idx, align 4
  %6 = getelementptr [1 x ptr], ptr %save_blk, i32 0, i32 %5
  %7 = load i32, ptr %idx, align 4
  %8 = getelementptr [1 x ptr], ptr %createdArray, i32 0, i32 %7
  %9 = load i32, ptr %8, align 4
  %10 = call ptr @malloc(i32 4)
  store i32 %9, ptr %10, align 4
  store ptr %10, ptr %6, align 8
  %11 = load i32, ptr %idx, align 4
  %12 = add nsw i32 %11, 1
  store i32 %12, ptr %idx, align 4
  br label %loop-cond

rest:                                             ; preds = %loop-cond
  %13 = getelementptr [1 x ptr], ptr %save_blk, i32 0, i32 0
  %14 = load i32, ptr %len, align 4
  %15 = call ptr @_ArrayToChannel(ptr %13, i32 %14)
  store ptr %15, ptr %c2, align 8
  %16 = load ptr, ptr %c2, align 8
  %17 = call i1 @_ShouldLinearLoop(ptr %16)
  br i1 %17, label %loop2, label %rest3

loop2:                                            ; preds = %loop2, %rest
  %18 = load ptr, ptr %c2, align 8
  %19 = call ptr @_ReadLinearChannel(ptr %18)
  %20 = load ptr, ptr %19, align 8
  %21 = call %Unit @free(ptr %19)
  store ptr %20, ptr %val, align 8
  %22 = call ptr @malloc(i32 4)
  store i32 1, ptr %22, align 4
  %23 = load ptr, ptr %val, align 8
  %24 = call %Unit @_WriteChannel(ptr %23, ptr %22)
  %25 = load ptr, ptr %c2, align 8
  %26 = call i1 @_ShouldLinearLoop(ptr %25)
  br i1 %26, label %loop2, label %rest3

rest3:                                            ; preds = %loop2, %rest
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

declare ptr @malloc(i32)

declare ptr @_ArrayToChannel(ptr, i32)

declare i1 @_ShouldLinearLoop(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare %Unit @_WriteChannel(ptr, ptr)
