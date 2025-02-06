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

define %Unit @nested(ptr %0) {
entry:
  %a = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %1 = load ptr, ptr %io, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %a, align 4
  %a1 = load i32, ptr %a, align 4
  %5 = icmp sle i32 %a1, 0
  br i1 %5, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %entry
  %a2 = load i32, ptr %a, align 4
  %6 = sub nsw i32 0, 5
  %7 = icmp slt i32 %a2, %6
  br i1 %7, label %mergeBlkOr, label %prevFalseOr

prevFalseOr:                                      ; preds = %prevTrueAnd
  %a3 = load i32, ptr %a, align 4
  %8 = icmp slt i32 %a3, 0
  br i1 %8, label %mergeBlkOr, label %prevFalseOr4

prevFalseOr4:                                     ; preds = %prevFalseOr
  %a5 = load i32, ptr %a, align 4
  %9 = icmp eq i32 %a5, 0
  br label %mergeBlkOr

mergeBlkOr:                                       ; preds = %prevFalseOr4, %prevFalseOr, %prevTrueAnd
  %logOr = phi i1 [ %7, %prevTrueAnd ], [ %8, %prevFalseOr ], [ %9, %prevFalseOr4 ]
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %mergeBlkOr, %entry
  %logAnd = phi i1 [ %5, %entry ], [ %logOr, %mergeBlkOr ]
  br i1 %logAnd, label %then, label %else31

then:                                             ; preds = %mergeBlkAnd
  %a6 = load i32, ptr %a, align 4
  %10 = sub nsw i32 0, 5
  %11 = icmp slt i32 %a6, %10
  br i1 %11, label %then7, label %else

then7:                                            ; preds = %then
  %12 = call i32 (...) @printf(ptr @0)
  br label %else

else:                                             ; preds = %then7, %then
  %a8 = load i32, ptr %a, align 4
  %13 = sub nsw i32 0, 5
  %14 = icmp slt i32 %a8, %13
  %15 = xor i1 %14, true
  br i1 %15, label %prevTrueAnd9, label %mergeBlkAnd12

prevTrueAnd9:                                     ; preds = %else
  %a10 = load i32, ptr %a, align 4
  %16 = sub nsw i32 0, 5
  %17 = icmp slt i32 %a10, %16
  br label %mergeBlkAnd12

mergeBlkAnd12:                                    ; preds = %prevTrueAnd9, %else
  %logAnd11 = phi i1 [ %15, %else ], [ %17, %prevTrueAnd9 ]
  br i1 %logAnd11, label %then13, label %else14

then13:                                           ; preds = %mergeBlkAnd12
  %18 = call i32 (...) @printf(ptr @1)
  br label %else14

else14:                                           ; preds = %then13, %mergeBlkAnd12
  %a15 = load i32, ptr %a, align 4
  %19 = sub nsw i32 0, 5
  %20 = icmp slt i32 %a15, %19
  %21 = xor i1 %20, true
  br i1 %21, label %prevTrueAnd16, label %mergeBlkAnd19

prevTrueAnd16:                                    ; preds = %else14
  %a17 = load i32, ptr %a, align 4
  %22 = icmp slt i32 %a17, 0
  br label %mergeBlkAnd19

mergeBlkAnd19:                                    ; preds = %prevTrueAnd16, %else14
  %logAnd18 = phi i1 [ %21, %else14 ], [ %22, %prevTrueAnd16 ]
  br i1 %logAnd18, label %then20, label %else21

then20:                                           ; preds = %mergeBlkAnd19
  %23 = call i32 (...) @printf(ptr @2)
  br label %else21

else21:                                           ; preds = %then20, %mergeBlkAnd19
  %a22 = load i32, ptr %a, align 4
  %24 = sub nsw i32 0, 5
  %25 = icmp slt i32 %a22, %24
  %26 = xor i1 %25, true
  br i1 %26, label %prevTrueAnd23, label %mergeBlkAnd28

prevTrueAnd23:                                    ; preds = %else21
  %a24 = load i32, ptr %a, align 4
  %27 = icmp slt i32 %a24, 0
  %28 = xor i1 %27, true
  br i1 %28, label %prevTrueAnd25, label %mergeBlkAnd28

prevTrueAnd25:                                    ; preds = %prevTrueAnd23
  %a26 = load i32, ptr %a, align 4
  %29 = icmp eq i32 %a26, 0
  br label %mergeBlkAnd28

mergeBlkAnd28:                                    ; preds = %prevTrueAnd25, %prevTrueAnd23, %else21
  %logAnd27 = phi i1 [ %26, %else21 ], [ %28, %prevTrueAnd23 ], [ %29, %prevTrueAnd25 ]
  br i1 %logAnd27, label %then29, label %else30

then29:                                           ; preds = %mergeBlkAnd28
  %30 = call i32 (...) @printf(ptr @3)
  br label %else30

else30:                                           ; preds = %then29, %mergeBlkAnd28
  br label %else31

else31:                                           ; preds = %else30, %mergeBlkAnd
  %a32 = load i32, ptr %a, align 4
  %31 = icmp sle i32 %a32, 0
  %32 = xor i1 %31, true
  br i1 %32, label %prevTrueAnd33, label %mergeBlkAnd36

prevTrueAnd33:                                    ; preds = %else31
  %a34 = load i32, ptr %a, align 4
  %33 = icmp eq i32 %a34, 0
  br label %mergeBlkAnd36

mergeBlkAnd36:                                    ; preds = %prevTrueAnd33, %else31
  %logAnd35 = phi i1 [ %32, %else31 ], [ %33, %prevTrueAnd33 ]
  br i1 %logAnd35, label %then37, label %else38

then37:                                           ; preds = %mergeBlkAnd36
  %34 = call i32 (...) @printf(ptr @4)
  br label %else38

else38:                                           ; preds = %then37, %mergeBlkAnd36
  %a39 = load i32, ptr %a, align 4
  %35 = icmp sle i32 %a39, 0
  %36 = xor i1 %35, true
  br i1 %36, label %prevTrueAnd40, label %mergeBlkAnd47

prevTrueAnd40:                                    ; preds = %else38
  %a41 = load i32, ptr %a, align 4
  %37 = icmp sge i32 %a41, 5
  br i1 %37, label %mergeBlkOr45, label %prevFalseOr42

prevFalseOr42:                                    ; preds = %prevTrueAnd40
  %a43 = load i32, ptr %a, align 4
  %38 = icmp slt i32 %a43, 5
  br label %mergeBlkOr45

mergeBlkOr45:                                     ; preds = %prevFalseOr42, %prevTrueAnd40
  %logOr44 = phi i1 [ %37, %prevTrueAnd40 ], [ %38, %prevFalseOr42 ]
  br label %mergeBlkAnd47

mergeBlkAnd47:                                    ; preds = %mergeBlkOr45, %else38
  %logAnd46 = phi i1 [ %36, %else38 ], [ %logOr44, %mergeBlkOr45 ]
  br i1 %logAnd46, label %then48, label %else55

then48:                                           ; preds = %mergeBlkAnd47
  %a49 = load i32, ptr %a, align 4
  %39 = icmp sge i32 %a49, 5
  br i1 %39, label %then50, label %else51

then50:                                           ; preds = %then48
  %40 = call i32 (...) @printf(ptr @5)
  br label %else51

else51:                                           ; preds = %then50, %then48
  %a52 = load i32, ptr %a, align 4
  %41 = icmp slt i32 %a52, 5
  br i1 %41, label %then53, label %else54

then53:                                           ; preds = %else51
  %42 = call i32 (...) @printf(ptr @6)
  br label %else54

else54:                                           ; preds = %then53, %else51
  br label %else55

else55:                                           ; preds = %else54, %mergeBlkAnd47
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %io = alloca ptr, align 8
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
  %4 = call ptr @_Execute(ptr @nested)
  store ptr %4, ptr %io, align 8
  %i3 = load i32, ptr %i, align 4
  %5 = call ptr @malloc(i32 4)
  store i32 %i3, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
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
