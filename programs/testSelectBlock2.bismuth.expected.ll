; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [14 x i8] c"Less than -5\0A\00", align 1
@1 = private unnamed_addr constant [23 x i8] c"Less than -5 - BROKEN\0A\00", align 1
@2 = private unnamed_addr constant [30 x i8] c"Less than 0; Greater than -5\0A\00", align 1
@3 = private unnamed_addr constant [7 x i8] c"ZERO!\0A\00", align 1
@4 = private unnamed_addr constant [13 x i8] c"Wrong zero!\0A\00", align 1
@5 = private unnamed_addr constant [16 x i8] c"Greater than 5\0A\00", align 1
@6 = private unnamed_addr constant [13 x i8] c"Less than 5\0A\00", align 1
@7 = private unnamed_addr constant [10 x i8] c"For %d:\0A\09\00", align 1

define %Unit @sel1(ptr %0) {
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
  %5 = icmp sle i32 %a1, 0
  br i1 %5, label %then, label %else12

then:                                             ; preds = %entry
  %a2 = load i32, ptr %a, align 4
  %6 = sub nsw i32 0, 5
  %7 = icmp slt i32 %a2, %6
  br i1 %7, label %then3, label %else

then3:                                            ; preds = %then
  %8 = call i32 (...) @printf(ptr @0)
  br label %if-cont

else:                                             ; preds = %then
  %a4 = load i32, ptr %a, align 4
  %9 = sub nsw i32 0, 5
  %10 = icmp slt i32 %a4, %9
  br i1 %10, label %then5, label %else6

then5:                                            ; preds = %else
  %11 = call i32 (...) @printf(ptr @1)
  br label %if-cont

else6:                                            ; preds = %else
  %a7 = load i32, ptr %a, align 4
  %12 = icmp slt i32 %a7, 0
  br i1 %12, label %then8, label %else9

then8:                                            ; preds = %else6
  %13 = call i32 (...) @printf(ptr @2)
  br label %if-cont

else9:                                            ; preds = %else6
  %a10 = load i32, ptr %a, align 4
  %14 = icmp eq i32 %a10, 0
  br i1 %14, label %then11, label %if-cont

then11:                                           ; preds = %else9
  %15 = call i32 (...) @printf(ptr @3)
  br label %if-cont

if-cont:                                          ; preds = %then11, %else9, %then8, %then5, %then3
  br label %if-cont21

else12:                                           ; preds = %entry
  %a13 = load i32, ptr %a, align 4
  %16 = icmp eq i32 %a13, 0
  br i1 %16, label %then14, label %else15

then14:                                           ; preds = %else12
  %17 = call i32 (...) @printf(ptr @4)
  br label %if-cont21

else15:                                           ; preds = %else12
  %a16 = load i32, ptr %a, align 4
  %18 = icmp sge i32 %a16, 5
  br i1 %18, label %then17, label %else18

then17:                                           ; preds = %else15
  %19 = call i32 (...) @printf(ptr @5)
  br label %if-cont21

else18:                                           ; preds = %else15
  %a19 = load i32, ptr %a, align 4
  %20 = icmp slt i32 %a19, 5
  br i1 %20, label %then20, label %if-cont21

then20:                                           ; preds = %else18
  %21 = call i32 (...) @printf(ptr @6)
  br label %if-cont21

if-cont21:                                        ; preds = %then20, %else18, %then17, %then14, %if-cont
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %c1 = alloca ptr, align 8
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = sub nsw i32 0, 10
  store i32 %1, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %2 = icmp sle i32 %i1, 15
  br i1 %2, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %i2 = load i32, ptr %i, align 4
  %3 = call i32 (...) @printf(ptr @7, i32 %i2)
  %4 = call ptr @_Execute(ptr @sel1)
  store ptr %4, ptr %c1, align 8
  %i3 = load i32, ptr %i, align 4
  %5 = call ptr @malloc(i32 4)
  store i32 %i3, ptr %5, align 4
  %6 = load ptr, ptr %c1, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %i4 = load i32, ptr %i, align 4
  %8 = add nsw i32 %i4, 1
  store i32 %8, ptr %i, align 4
  %i5 = load i32, ptr %i, align 4
  %9 = icmp sle i32 %i5, 15
  br i1 %9, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %10 = sub nsw i32 0, 1
  %11 = call ptr @malloc(i32 4)
  store i32 %10, ptr %11, align 4
  %12 = load ptr, ptr %c, align 8
  %13 = call %Unit @_WriteChannel(ptr %12, ptr %11)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @_Execute(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
