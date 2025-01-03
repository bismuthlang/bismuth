; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [34 x i8] c"The %dth fibonacci number is: %d\0A\00", align 1

define %Unit @fib(ptr %0) {
entry:
  %v2 = alloca i32, align 4
  %v1 = alloca i32, align 4
  %f2 = alloca ptr, align 8
  %f1 = alloca ptr, align 8
  %n = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %n, align 4
  %n1 = load i32, ptr %n, align 4
  %5 = icmp eq i32 %n1, 0
  br i1 %5, label %mergeBlkOr, label %prevFalseOr

prevFalseOr:                                      ; preds = %entry
  %n2 = load i32, ptr %n, align 4
  %6 = icmp eq i32 %n2, 1
  br label %mergeBlkOr

mergeBlkOr:                                       ; preds = %prevFalseOr, %entry
  %logOr = phi i1 [ %5, %entry ], [ %6, %prevFalseOr ]
  br i1 %logOr, label %then, label %else

then:                                             ; preds = %mergeBlkOr
  %7 = call ptr @malloc(i32 4)
  store i32 1, ptr %7, align 4
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  ret %Unit zeroinitializer

else:                                             ; preds = %mergeBlkOr
  %10 = call ptr @_Execute(ptr @fib)
  store ptr %10, ptr %f1, align 8
  %11 = call ptr @_Execute(ptr @fib)
  store ptr %11, ptr %f2, align 8
  %n3 = load i32, ptr %n, align 4
  %12 = sub nsw i32 %n3, 1
  %13 = call ptr @malloc(i32 4)
  store i32 %12, ptr %13, align 4
  %14 = load ptr, ptr %f1, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  %n4 = load i32, ptr %n, align 4
  %16 = sub nsw i32 %n4, 2
  %17 = call ptr @malloc(i32 4)
  store i32 %16, ptr %17, align 4
  %18 = load ptr, ptr %f2, align 8
  %19 = call %Unit @_WriteChannel(ptr %18, ptr %17)
  %20 = load ptr, ptr %f1, align 8
  %21 = call ptr @_ReadLinearChannel(ptr %20)
  %22 = load i32, ptr %21, align 4
  %23 = call %Unit @free(ptr %21)
  store i32 %22, ptr %v1, align 4
  %24 = load ptr, ptr %f2, align 8
  %25 = call ptr @_ReadLinearChannel(ptr %24)
  %26 = load i32, ptr %25, align 4
  %27 = call %Unit @free(ptr %25)
  store i32 %26, ptr %v2, align 4
  %v15 = load i32, ptr %v1, align 4
  %v26 = load i32, ptr %v2, align 4
  %28 = add nsw i32 %v15, %v26
  %29 = call ptr @malloc(i32 4)
  store i32 %28, ptr %29, align 4
  %30 = load ptr, ptr %c, align 8
  %31 = call %Unit @_WriteChannel(ptr %30, ptr %29)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %i = alloca i32, align 4
  %f = alloca ptr, align 8
  %current = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 1, ptr %current, align 4
  %current1 = load i32, ptr %current, align 4
  %1 = icmp slt i32 %current1, 20
  br i1 %1, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %2 = call ptr @_Execute(ptr @fib)
  store ptr %2, ptr %f, align 8
  %current2 = load i32, ptr %current, align 4
  %3 = call ptr @malloc(i32 4)
  store i32 %current2, ptr %3, align 4
  %4 = load ptr, ptr %f, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = load ptr, ptr %f, align 8
  %7 = call ptr @_ReadLinearChannel(ptr %6)
  %8 = load i32, ptr %7, align 4
  %9 = call %Unit @free(ptr %7)
  store i32 %8, ptr %i, align 4
  %current3 = load i32, ptr %current, align 4
  %i4 = load i32, ptr %i, align 4
  %10 = call i32 (...) @printf(ptr @0, i32 %current3, i32 %i4)
  %current5 = load i32, ptr %current, align 4
  %11 = add nsw i32 %current5, 1
  store i32 %11, ptr %current, align 4
  %current6 = load i32, ptr %current, align 4
  %12 = icmp slt i32 %current6, 20
  br i1 %12, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %13 = sub nsw i32 0, 1
  %14 = call ptr @malloc(i32 4)
  store i32 %13, ptr %14, align 4
  %15 = load ptr, ptr %c, align 8
  %16 = call %Unit @_WriteChannel(ptr %15, ptr %14)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
