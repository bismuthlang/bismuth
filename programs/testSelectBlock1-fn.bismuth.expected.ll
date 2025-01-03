; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [12 x i8] c"CASE 1 (10)\00", align 1
@1 = private unnamed_addr constant [11 x i8] c"CASE 2 (5)\00", align 1
@2 = private unnamed_addr constant [11 x i8] c"CASE 3 (0)\00", align 1
@3 = private unnamed_addr constant [11 x i8] c"CASE 4 (a)\00", align 1
@4 = private unnamed_addr constant [21 x i8] c"CASE IMPOSSIBLE (-1)\00", align 1
@5 = private unnamed_addr constant [12 x i8] c"f(%d) = %s\0A\00", align 1

define ptr @selReturnOne(i32 %0) {
entry:
  %a = alloca i32, align 4
  store i32 %0, ptr %a, align 4
  %a1 = load i32, ptr %a, align 4
  %1 = icmp sgt i32 %a1, 10
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  ret ptr @0

else:                                             ; preds = %entry
  %a2 = load i32, ptr %a, align 4
  %2 = icmp sgt i32 %a2, 0
  br i1 %2, label %then3, label %else4

then3:                                            ; preds = %else
  ret ptr @1

else4:                                            ; preds = %else
  %a5 = load i32, ptr %a, align 4
  %3 = icmp eq i32 %a5, 0
  br i1 %3, label %then6, label %else7

then6:                                            ; preds = %else4
  ret ptr @2

else7:                                            ; preds = %else4
  %a8 = load i32, ptr %a, align 4
  %4 = icmp slt i32 %a8, 0
  br i1 %4, label %then9, label %if-cont

then9:                                            ; preds = %else7
  ret ptr @3

if-cont:                                          ; preds = %else7
  ret ptr @4
}

define %Unit @program(ptr %0) {
entry:
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
  %i3 = load i32, ptr %i, align 4
  %3 = call ptr @selReturnOne(i32 %i3)
  %4 = call i32 (...) @printf(ptr @5, i32 %i2, ptr %3)
  %i4 = load i32, ptr %i, align 4
  %5 = add nsw i32 %i4, 1
  store i32 %5, ptr %i, align 4
  %i5 = load i32, ptr %i, align 4
  %6 = icmp sle i32 %i5, 15
  br i1 %6, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %7 = sub nsw i32 0, 1
  %8 = call ptr @malloc(i32 4)
  store i32 %7, ptr %8, align 4
  %9 = load ptr, ptr %c, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
