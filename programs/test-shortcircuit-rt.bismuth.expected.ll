; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [31 x i8] c"Needs at least two arguments!\0A\00", align 1
@1 = private unnamed_addr constant [23 x i8] c"i = %d, argCount = %d\0A\00", align 1
@2 = private unnamed_addr constant [18 x i8] c"%d > 0 && %d = 2\0A\00", align 1
@3 = private unnamed_addr constant [18 x i8] c"%d > 0 || %d = 2\0A\00", align 1
@4 = private unnamed_addr constant [8 x i8] c"true + \00", align 1
@5 = private unnamed_addr constant [9 x i8] c"false + \00", align 1
@6 = private unnamed_addr constant [6 x i8] c"true\0A\00", align 1
@7 = private unnamed_addr constant [7 x i8] c"false\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %test2 = alloca i1, align 1
  %test = alloca i1, align 1
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 1, ptr %i, align 4
  %1 = call i32 @getArgCount()
  %2 = icmp slt i32 %1, 2
  br i1 %2, label %then, label %else

then:                                             ; preds = %entry
  %3 = call i32 (ptr, ...) @printf(ptr @0)
  %4 = sub nsw i32 0, 1
  %5 = call ptr @malloc(i32 4)
  store i32 %4, ptr %5, align 4
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  ret %Unit zeroinitializer

else:                                             ; preds = %entry
  %i1 = load i32, ptr %i, align 4
  %8 = call i32 @getArgCount()
  %9 = icmp slt i32 %i1, %8
  br i1 %9, label %loop, label %rest

loop:                                             ; preds = %if-cont19, %else
  %i2 = load i32, ptr %i, align 4
  %10 = call i32 @getArgCount()
  %11 = call i32 (ptr, ...) @printf(ptr @1, i32 %i2, i32 %10)
  %i3 = load i32, ptr %i, align 4
  %12 = call i32 @getIntArg(i32 %i3)
  store i32 %12, ptr %a, align 4
  %i4 = load i32, ptr %i, align 4
  %13 = add nsw i32 %i4, 1
  %14 = call i32 @getIntArg(i32 %13)
  store i32 %14, ptr %b, align 4
  %a5 = load i32, ptr %a, align 4
  %b6 = load i32, ptr %b, align 4
  %15 = call i32 (ptr, ...) @printf(ptr @2, i32 %a5, i32 %b6)
  %a7 = load i32, ptr %a, align 4
  %16 = icmp sgt i32 %a7, 0
  br i1 %16, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %loop
  %b8 = load i32, ptr %b, align 4
  %17 = icmp eq i32 %b8, 2
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %prevTrueAnd, %loop
  %logAnd = phi i1 [ %16, %loop ], [ %17, %prevTrueAnd ]
  store i1 %logAnd, ptr %test, align 1
  %a9 = load i32, ptr %a, align 4
  %b10 = load i32, ptr %b, align 4
  %18 = call i32 (ptr, ...) @printf(ptr @3, i32 %a9, i32 %b10)
  %a11 = load i32, ptr %a, align 4
  %19 = icmp sgt i32 %a11, 0
  br i1 %19, label %mergeBlkOr, label %prevFalseOr

prevFalseOr:                                      ; preds = %mergeBlkAnd
  %b12 = load i32, ptr %b, align 4
  %20 = icmp eq i32 %b12, 2
  br label %mergeBlkOr

mergeBlkOr:                                       ; preds = %prevFalseOr, %mergeBlkAnd
  %logOr = phi i1 [ %19, %mergeBlkAnd ], [ %20, %prevFalseOr ]
  store i1 %logOr, ptr %test2, align 1
  %test13 = load i1, ptr %test, align 1
  br i1 %test13, label %then14, label %else15

then14:                                           ; preds = %mergeBlkOr
  %21 = call i32 (ptr, ...) @printf(ptr @4)
  br label %if-cont

else15:                                           ; preds = %mergeBlkOr
  %22 = call i32 (ptr, ...) @printf(ptr @5)
  br label %if-cont

if-cont:                                          ; preds = %else15, %then14
  %test216 = load i1, ptr %test2, align 1
  br i1 %test216, label %then17, label %else18

then17:                                           ; preds = %if-cont
  %23 = call i32 (ptr, ...) @printf(ptr @6)
  br label %if-cont19

else18:                                           ; preds = %if-cont
  %24 = call i32 (ptr, ...) @printf(ptr @7)
  br label %if-cont19

if-cont19:                                        ; preds = %else18, %then17
  %i20 = load i32, ptr %i, align 4
  %25 = add nsw i32 %i20, 2
  store i32 %25, ptr %i, align 4
  %i21 = load i32, ptr %i, align 4
  %26 = call i32 @getArgCount()
  %27 = icmp slt i32 %i21, %26
  br i1 %27, label %loop, label %rest

rest:                                             ; preds = %if-cont19, %else
  %28 = call ptr @malloc(i32 4)
  store i32 0, ptr %28, align 4
  %29 = load ptr, ptr %c, align 8
  %30 = call %Unit @_WriteChannel(ptr %29, ptr %28)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare i32 @getArgCount()

declare i32 @getIntArg(i32)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
