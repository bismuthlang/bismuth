; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [8 x i8] c"%d, %d\0A\00", align 1
@1 = private unnamed_addr constant [21 x i8] c"x is %d, x < 4 = %d\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %y = alloca i32, align 4
  %x = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %x, align 4
  store i32 0, ptr %y, align 4
  %x1 = load i32, ptr %x, align 4
  %1 = icmp slt i32 %x1, 4
  br i1 %1, label %loop, label %rest12

loop:                                             ; preds = %rest, %entry
  store i32 0, ptr %y, align 4
  %y2 = load i32, ptr %y, align 4
  %2 = icmp slt i32 %y2, 4
  br i1 %2, label %loop3, label %rest

loop3:                                            ; preds = %loop3, %loop
  %x4 = load i32, ptr %x, align 4
  %y5 = load i32, ptr %y, align 4
  %3 = call i32 (...) @printf(ptr @0, i32 %x4, i32 %y5)
  %y6 = load i32, ptr %y, align 4
  %4 = add nsw i32 %y6, 1
  store i32 %4, ptr %y, align 4
  %y7 = load i32, ptr %y, align 4
  %5 = icmp slt i32 %y7, 4
  br i1 %5, label %loop3, label %rest

rest:                                             ; preds = %loop3, %loop
  %x8 = load i32, ptr %x, align 4
  %6 = add nsw i32 %x8, 1
  store i32 %6, ptr %x, align 4
  %x9 = load i32, ptr %x, align 4
  %x10 = load i32, ptr %x, align 4
  %7 = icmp slt i32 %x10, 4
  %8 = call i32 (...) @printf(ptr @1, i32 %x9, i1 %7)
  %x11 = load i32, ptr %x, align 4
  %9 = icmp slt i32 %x11, 4
  br i1 %9, label %loop, label %rest12

rest12:                                           ; preds = %rest, %entry
  %10 = sub nsw i32 0, 1
  %11 = call ptr @malloc(i32 4)
  store i32 %10, ptr %11, align 4
  %12 = load ptr, ptr %c, align 8
  %13 = call %Unit @_WriteChannel(ptr %12, ptr %11)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
