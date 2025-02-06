; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@1 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@2 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %addStream = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @BinaryCounter)
  store ptr %1, ptr %addStream, align 8
  %2 = call ptr @_Execute(ptr @Num7)
  %3 = call ptr @malloc(i32 8)
  store ptr %2, ptr %3, align 8
  %4 = load ptr, ptr %addStream, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = call ptr @_Execute(ptr @Num5)
  %7 = call ptr @malloc(i32 8)
  store ptr %6, ptr %7, align 8
  %8 = load ptr, ptr %addStream, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  %10 = load ptr, ptr %addStream, align 8
  %11 = call i1 @_ShouldLinearLoop(ptr %10)
  br i1 %11, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %12 = load ptr, ptr %addStream, align 8
  %13 = call ptr @_ReadLinearChannel(ptr %12)
  %14 = load i1, ptr %13, align 1
  %15 = call %Unit @free(ptr %13)
  %16 = call ptr @"program::#lambda"(i1 %14)
  %17 = call i32 (ptr, ...) @printf(ptr @0, ptr %16)
  %18 = load ptr, ptr %addStream, align 8
  %19 = call i1 @_ShouldLinearLoop(ptr %18)
  br i1 %19, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %20 = call i32 (ptr, ...) @printf(ptr @3)
  %21 = call ptr @malloc(i32 4)
  store i32 0, ptr %21, align 4
  %22 = load ptr, ptr %c, align 8
  %23 = call %Unit @_WriteChannel(ptr %22, ptr %21)
  ret %Unit zeroinitializer
}

define i1 @XOR(i1 %0, i1 %1) {
entry:
  %b = alloca i1, align 1
  %a = alloca i1, align 1
  store i1 %0, ptr %a, align 1
  store i1 %1, ptr %b, align 1
  %a1 = load i1, ptr %a, align 1
  br i1 %a1, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %entry
  %b2 = load i1, ptr %b, align 1
  %2 = xor i1 %b2, true
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %prevTrueAnd, %entry
  %logAnd = phi i1 [ %a1, %entry ], [ %2, %prevTrueAnd ]
  br i1 %logAnd, label %mergeBlkOr, label %prevFalseOr

prevFalseOr:                                      ; preds = %mergeBlkAnd
  %a3 = load i1, ptr %a, align 1
  %3 = xor i1 %a3, true
  br i1 %3, label %prevTrueAnd4, label %mergeBlkAnd7

prevTrueAnd4:                                     ; preds = %prevFalseOr
  %b5 = load i1, ptr %b, align 1
  br label %mergeBlkAnd7

mergeBlkAnd7:                                     ; preds = %prevTrueAnd4, %prevFalseOr
  %logAnd6 = phi i1 [ %3, %prevFalseOr ], [ %b5, %prevTrueAnd4 ]
  br label %mergeBlkOr

mergeBlkOr:                                       ; preds = %mergeBlkAnd7, %mergeBlkAnd
  %logOr = phi i1 [ %logAnd, %mergeBlkAnd ], [ %logAnd6, %mergeBlkAnd7 ]
  ret i1 %logOr
}

define %Unit @BinaryCounter(ptr %0) {
entry:
  %val.0 = alloca i1, align 1
  %car = alloca i1, align 1
  %sum = alloca i1, align 1
  %xor = alloca i1, align 1
  %val2 = alloca i1, align 1
  %looped2 = alloca i1, align 1
  %val = alloca i1, align 1
  %carry = alloca i1, align 1
  %i2 = alloca ptr, align 8
  %i1 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store ptr %3, ptr %i1, align 8
  %5 = load ptr, ptr %c, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load ptr, ptr %6, align 8
  %8 = call %Unit @free(ptr %6)
  store ptr %7, ptr %i2, align 8
  store i1 false, ptr %carry, align 1
  %9 = load ptr, ptr %i1, align 8
  %10 = call i1 @_ShouldLinearLoop(ptr %9)
  br i1 %10, label %loop, label %rest16

loop:                                             ; preds = %mergeBlkOr, %entry
  %11 = load ptr, ptr %i1, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load i1, ptr %12, align 1
  %14 = call %Unit @free(ptr %12)
  store i1 %13, ptr %val, align 1
  store i1 false, ptr %looped2, align 1
  store i1 false, ptr %val2, align 1
  br label %aw-cond

aw-cond:                                          ; preds = %loop2, %loop
  %looped21 = load i1, ptr %looped2, align 1
  %15 = xor i1 %looped21, true
  br i1 %15, label %aw-then, label %rest

aw-then:                                          ; preds = %aw-cond
  %16 = load ptr, ptr %i2, align 8
  %17 = call i1 @_ShouldLinearAcceptWhileLoop(ptr %16)
  br i1 %17, label %loop2, label %rest

loop2:                                            ; preds = %aw-then
  %18 = load ptr, ptr %i2, align 8
  %19 = call ptr @_ReadLinearChannel(ptr %18)
  %20 = load i1, ptr %19, align 1
  %21 = call %Unit @free(ptr %19)
  store i1 %20, ptr %val2, align 1
  store i1 true, ptr %looped2, align 1
  br label %aw-cond

rest:                                             ; preds = %aw-then, %aw-cond
  %val3 = load i1, ptr %val, align 1
  %val24 = load i1, ptr %val2, align 1
  %22 = call i1 @XOR(i1 %val3, i1 %val24)
  store i1 %22, ptr %xor, align 1
  %xor5 = load i1, ptr %xor, align 1
  %carry6 = load i1, ptr %carry, align 1
  %23 = call i1 @XOR(i1 %xor5, i1 %carry6)
  store i1 %23, ptr %sum, align 1
  %xor7 = load i1, ptr %xor, align 1
  br i1 %xor7, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %rest
  %carry8 = load i1, ptr %carry, align 1
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %prevTrueAnd, %rest
  %logAnd = phi i1 [ %xor7, %rest ], [ %carry8, %prevTrueAnd ]
  br i1 %logAnd, label %mergeBlkOr, label %prevFalseOr

prevFalseOr:                                      ; preds = %mergeBlkAnd
  %val9 = load i1, ptr %val, align 1
  br i1 %val9, label %prevTrueAnd10, label %mergeBlkAnd13

prevTrueAnd10:                                    ; preds = %prevFalseOr
  %val211 = load i1, ptr %val2, align 1
  br label %mergeBlkAnd13

mergeBlkAnd13:                                    ; preds = %prevTrueAnd10, %prevFalseOr
  %logAnd12 = phi i1 [ %val9, %prevFalseOr ], [ %val211, %prevTrueAnd10 ]
  br label %mergeBlkOr

mergeBlkOr:                                       ; preds = %mergeBlkAnd13, %mergeBlkAnd
  %logOr = phi i1 [ %logAnd, %mergeBlkAnd ], [ %logAnd12, %mergeBlkAnd13 ]
  store i1 %logOr, ptr %car, align 1
  %24 = load ptr, ptr %c, align 8
  %25 = call %Unit @_ContractChannel(ptr %24)
  %sum14 = load i1, ptr %sum, align 1
  %26 = call ptr @malloc(i32 1)
  store i1 %sum14, ptr %26, align 1
  %27 = load ptr, ptr %c, align 8
  %28 = call %Unit @_WriteChannel(ptr %27, ptr %26)
  %car15 = load i1, ptr %car, align 1
  store i1 %car15, ptr %carry, align 1
  %29 = load ptr, ptr %i1, align 8
  %30 = call i1 @_ShouldLinearLoop(ptr %29)
  br i1 %30, label %loop, label %rest16

rest16:                                           ; preds = %mergeBlkOr, %entry
  %31 = load ptr, ptr %i2, align 8
  %32 = call i1 @_ShouldLinearLoop(ptr %31)
  br i1 %32, label %loop17, label %rest25

loop17:                                           ; preds = %mergeBlkAnd24, %rest16
  %33 = load ptr, ptr %i2, align 8
  %34 = call ptr @_ReadLinearChannel(ptr %33)
  %35 = load i1, ptr %34, align 1
  %36 = call %Unit @free(ptr %34)
  store i1 %35, ptr %val.0, align 1
  %37 = load ptr, ptr %c, align 8
  %38 = call %Unit @_ContractChannel(ptr %37)
  %val.018 = load i1, ptr %val.0, align 1
  %carry19 = load i1, ptr %carry, align 1
  %39 = call i1 @XOR(i1 %val.018, i1 %carry19)
  %40 = call ptr @malloc(i32 1)
  store i1 %39, ptr %40, align 1
  %41 = load ptr, ptr %c, align 8
  %42 = call %Unit @_WriteChannel(ptr %41, ptr %40)
  %val.020 = load i1, ptr %val.0, align 1
  br i1 %val.020, label %prevTrueAnd21, label %mergeBlkAnd24

prevTrueAnd21:                                    ; preds = %loop17
  %carry22 = load i1, ptr %carry, align 1
  br label %mergeBlkAnd24

mergeBlkAnd24:                                    ; preds = %prevTrueAnd21, %loop17
  %logAnd23 = phi i1 [ %val.020, %loop17 ], [ %carry22, %prevTrueAnd21 ]
  store i1 %logAnd23, ptr %carry, align 1
  %43 = load ptr, ptr %i2, align 8
  %44 = call i1 @_ShouldLinearLoop(ptr %43)
  br i1 %44, label %loop17, label %rest25

rest25:                                           ; preds = %mergeBlkAnd24, %rest16
  %carry26 = load i1, ptr %carry, align 1
  br i1 %carry26, label %then, label %else

then:                                             ; preds = %rest25
  %45 = load ptr, ptr %c, align 8
  %46 = call %Unit @_ContractChannel(ptr %45)
  %carry27 = load i1, ptr %carry, align 1
  %47 = call ptr @malloc(i32 1)
  store i1 %carry27, ptr %47, align 1
  %48 = load ptr, ptr %c, align 8
  %49 = call %Unit @_WriteChannel(ptr %48, ptr %47)
  br label %else

else:                                             ; preds = %then, %rest25
  %50 = load ptr, ptr %c, align 8
  %51 = call %Unit @_WeakenChannel(ptr %50)
  ret %Unit zeroinitializer
}

define %Unit @Num7(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call %Unit @_ContractChannel(ptr %1)
  %3 = call ptr @malloc(i32 1)
  store i1 true, ptr %3, align 1
  %4 = load ptr, ptr %c, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_ContractChannel(ptr %6)
  %8 = call ptr @malloc(i32 1)
  store i1 true, ptr %8, align 1
  %9 = load ptr, ptr %c, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = load ptr, ptr %c, align 8
  %12 = call %Unit @_ContractChannel(ptr %11)
  %13 = call ptr @malloc(i32 1)
  store i1 true, ptr %13, align 1
  %14 = load ptr, ptr %c, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  %16 = load ptr, ptr %c, align 8
  %17 = call %Unit @_WeakenChannel(ptr %16)
  ret %Unit zeroinitializer
}

define %Unit @Num5(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call %Unit @_ContractChannel(ptr %1)
  %3 = call ptr @malloc(i32 1)
  store i1 true, ptr %3, align 1
  %4 = load ptr, ptr %c, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_ContractChannel(ptr %6)
  %8 = call ptr @malloc(i32 1)
  store i1 false, ptr %8, align 1
  %9 = load ptr, ptr %c, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = load ptr, ptr %c, align 8
  %12 = call %Unit @_ContractChannel(ptr %11)
  %13 = call ptr @malloc(i32 1)
  store i1 true, ptr %13, align 1
  %14 = load ptr, ptr %c, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  %16 = load ptr, ptr %c, align 8
  %17 = call %Unit @_WeakenChannel(ptr %16)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @_Execute(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare i1 @_ShouldLinearLoop(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

define private ptr @"program::#lambda"(i1 %0) {
entry:
  %b = alloca i1, align 1
  store i1 %0, ptr %b, align 1
  %b1 = load i1, ptr %b, align 1
  br i1 %b1, label %then, label %else

then:                                             ; preds = %entry
  ret ptr @1

else:                                             ; preds = %entry
  ret ptr @2
}

declare i1 @_ShouldLinearAcceptWhileLoop(ptr)

declare %Unit @_ContractChannel(ptr)

declare %Unit @_WeakenChannel(ptr)
