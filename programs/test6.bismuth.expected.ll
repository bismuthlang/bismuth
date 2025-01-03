; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [12 x i8] c"CASE 1 (10)\00", align 1
@1 = private unnamed_addr constant [11 x i8] c"CASE 2 (5)\00", align 1
@2 = private unnamed_addr constant [11 x i8] c"CASE 3 (0)\00", align 1
@3 = private unnamed_addr constant [11 x i8] c"CASE 4 (a)\00", align 1
@4 = private unnamed_addr constant [21 x i8] c"CASE IMPOSSIBLE (-1)\00", align 1
@5 = private unnamed_addr constant [12 x i8] c"f(%d) = %s\0A\00", align 1

define %Unit @selReturnOne(ptr %0) {
entry:
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %a, align 4
  %a1 = load i32, ptr %a, align 4
  %5 = icmp sgt i32 %a1, 10
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  %6 = call ptr @malloc(i32 8)
  store ptr @0, ptr %6, align 8
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer

else:                                             ; preds = %entry
  %a2 = load i32, ptr %a, align 4
  %9 = icmp sgt i32 %a2, 0
  br i1 %9, label %then3, label %else4

then3:                                            ; preds = %else
  %10 = call ptr @malloc(i32 8)
  store ptr @1, ptr %10, align 8
  %11 = load ptr, ptr %c, align 8
  %12 = call %Unit @_WriteChannel(ptr %11, ptr %10)
  ret %Unit zeroinitializer

else4:                                            ; preds = %else
  %a5 = load i32, ptr %a, align 4
  %13 = icmp eq i32 %a5, 0
  br i1 %13, label %then6, label %else7

then6:                                            ; preds = %else4
  %14 = call ptr @malloc(i32 8)
  store ptr @2, ptr %14, align 8
  %15 = load ptr, ptr %c, align 8
  %16 = call %Unit @_WriteChannel(ptr %15, ptr %14)
  ret %Unit zeroinitializer

else7:                                            ; preds = %else4
  %a8 = load i32, ptr %a, align 4
  %17 = icmp slt i32 %a8, 0
  br i1 %17, label %then9, label %if-cont

then9:                                            ; preds = %else7
  %18 = call ptr @malloc(i32 8)
  store ptr @3, ptr %18, align 8
  %19 = load ptr, ptr %c, align 8
  %20 = call %Unit @_WriteChannel(ptr %19, ptr %18)
  ret %Unit zeroinitializer

if-cont:                                          ; preds = %else7
  %21 = call ptr @malloc(i32 8)
  store ptr @4, ptr %21, align 8
  %22 = load ptr, ptr %c, align 8
  %23 = call %Unit @_WriteChannel(ptr %22, ptr %21)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %s = alloca ptr, align 8
  %tmp = alloca ptr, align 8
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = sub nsw i32 0, 10
  store i32 %1, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %2 = icmp sle i32 %i1, 15
  br i1 %2, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %3 = call ptr @_Execute(ptr @selReturnOne)
  store ptr %3, ptr %tmp, align 8
  %i2 = load i32, ptr %i, align 4
  %4 = call ptr @malloc(i32 4)
  store i32 %i2, ptr %4, align 4
  %5 = load ptr, ptr %tmp, align 8
  %6 = call %Unit @_WriteChannel(ptr %5, ptr %4)
  %7 = load ptr, ptr %tmp, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load ptr, ptr %8, align 8
  %10 = call %Unit @free(ptr %8)
  store ptr %9, ptr %s, align 8
  %i3 = load i32, ptr %i, align 4
  %s4 = load ptr, ptr %s, align 8
  %11 = call i32 (...) @printf(ptr @5, i32 %i3, ptr %s4)
  %i5 = load i32, ptr %i, align 4
  %12 = add nsw i32 %i5, 1
  store i32 %12, ptr %i, align 4
  %i6 = load i32, ptr %i, align 4
  %13 = icmp sle i32 %i6, 15
  br i1 %13, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %14 = sub nsw i32 0, 1
  %15 = call ptr @malloc(i32 4)
  store i32 %14, ptr %15, align 4
  %16 = load ptr, ptr %c, align 8
  %17 = call %Unit @_WriteChannel(ptr %16, ptr %15)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
