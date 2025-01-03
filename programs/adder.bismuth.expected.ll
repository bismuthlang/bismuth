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
  %val = alloca i1, align 1
  %car = alloca i1, align 1
  %sum = alloca i1, align 1
  %xor = alloca i1, align 1
  %val2 = alloca i1, align 1
  %looped2 = alloca i1, align 1
  %val1 = alloca i1, align 1
  %looped1 = alloca i1, align 1
  %shouldLoop = alloca i1, align 1
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
  store i1 true, ptr %shouldLoop, align 1
  %shouldLoop1 = load i1, ptr %shouldLoop, align 1
  br i1 %shouldLoop1, label %loop, label %rest28

loop:                                             ; preds = %mergeBlkOr, %entry
  store i1 false, ptr %looped1, align 1
  store i1 false, ptr %val1, align 1
  br label %aw-cond

aw-cond:                                          ; preds = %loop3, %loop
  %looped12 = load i1, ptr %looped1, align 1
  %9 = xor i1 %looped12, true
  br i1 %9, label %aw-then, label %rest

aw-then:                                          ; preds = %aw-cond
  %10 = load ptr, ptr %i1, align 8
  %11 = call i1 @_ShouldLinearAcceptWhileLoop(ptr %10)
  br i1 %11, label %loop3, label %rest

loop3:                                            ; preds = %aw-then
  %12 = load ptr, ptr %i1, align 8
  %13 = call ptr @_ReadLinearChannel(ptr %12)
  %14 = load i1, ptr %13, align 1
  %15 = call %Unit @free(ptr %13)
  store i1 %14, ptr %val1, align 1
  store i1 true, ptr %looped1, align 1
  br label %aw-cond

rest:                                             ; preds = %aw-then, %aw-cond
  store i1 false, ptr %looped2, align 1
  store i1 false, ptr %val2, align 1
  br label %aw-cond4

aw-cond4:                                         ; preds = %loop7, %rest
  %looped25 = load i1, ptr %looped2, align 1
  %16 = xor i1 %looped25, true
  br i1 %16, label %aw-then6, label %rest8

aw-then6:                                         ; preds = %aw-cond4
  %17 = load ptr, ptr %i2, align 8
  %18 = call i1 @_ShouldLinearAcceptWhileLoop(ptr %17)
  br i1 %18, label %loop7, label %rest8

loop7:                                            ; preds = %aw-then6
  %19 = load ptr, ptr %i2, align 8
  %20 = call ptr @_ReadLinearChannel(ptr %19)
  %21 = load i1, ptr %20, align 1
  %22 = call %Unit @free(ptr %20)
  store i1 %21, ptr %val2, align 1
  store i1 true, ptr %looped2, align 1
  br label %aw-cond4

rest8:                                            ; preds = %aw-then6, %aw-cond4
  %looped19 = load i1, ptr %looped1, align 1
  br i1 %looped19, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %rest8
  %looped210 = load i1, ptr %looped2, align 1
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %prevTrueAnd, %rest8
  %logAnd = phi i1 [ %looped19, %rest8 ], [ %looped210, %prevTrueAnd ]
  store i1 %logAnd, ptr %shouldLoop, align 1
  %val111 = load i1, ptr %val1, align 1
  %val212 = load i1, ptr %val2, align 1
  %23 = call i1 @XOR(i1 %val111, i1 %val212)
  store i1 %23, ptr %xor, align 1
  %xor13 = load i1, ptr %xor, align 1
  %carry14 = load i1, ptr %carry, align 1
  %24 = call i1 @XOR(i1 %xor13, i1 %carry14)
  store i1 %24, ptr %sum, align 1
  %xor15 = load i1, ptr %xor, align 1
  br i1 %xor15, label %prevTrueAnd16, label %mergeBlkAnd19

prevTrueAnd16:                                    ; preds = %mergeBlkAnd
  %carry17 = load i1, ptr %carry, align 1
  br label %mergeBlkAnd19

mergeBlkAnd19:                                    ; preds = %prevTrueAnd16, %mergeBlkAnd
  %logAnd18 = phi i1 [ %xor15, %mergeBlkAnd ], [ %carry17, %prevTrueAnd16 ]
  br i1 %logAnd18, label %mergeBlkOr, label %prevFalseOr

prevFalseOr:                                      ; preds = %mergeBlkAnd19
  %val120 = load i1, ptr %val1, align 1
  br i1 %val120, label %prevTrueAnd21, label %mergeBlkAnd24

prevTrueAnd21:                                    ; preds = %prevFalseOr
  %val222 = load i1, ptr %val2, align 1
  br label %mergeBlkAnd24

mergeBlkAnd24:                                    ; preds = %prevTrueAnd21, %prevFalseOr
  %logAnd23 = phi i1 [ %val120, %prevFalseOr ], [ %val222, %prevTrueAnd21 ]
  br label %mergeBlkOr

mergeBlkOr:                                       ; preds = %mergeBlkAnd24, %mergeBlkAnd19
  %logOr = phi i1 [ %logAnd18, %mergeBlkAnd19 ], [ %logAnd23, %mergeBlkAnd24 ]
  store i1 %logOr, ptr %car, align 1
  %25 = load ptr, ptr %c, align 8
  %26 = call %Unit @_ContractChannel(ptr %25)
  %sum25 = load i1, ptr %sum, align 1
  %27 = call ptr @malloc(i32 1)
  store i1 %sum25, ptr %27, align 1
  %28 = load ptr, ptr %c, align 8
  %29 = call %Unit @_WriteChannel(ptr %28, ptr %27)
  %car26 = load i1, ptr %car, align 1
  store i1 %car26, ptr %carry, align 1
  %shouldLoop27 = load i1, ptr %shouldLoop, align 1
  br i1 %shouldLoop27, label %loop, label %rest28

rest28:                                           ; preds = %mergeBlkOr, %entry
  %30 = load ptr, ptr %i1, align 8
  %31 = call i1 @_ShouldLinearLoop(ptr %30)
  br i1 %31, label %loop29, label %rest37

loop29:                                           ; preds = %mergeBlkAnd36, %rest28
  %32 = load ptr, ptr %i1, align 8
  %33 = call ptr @_ReadLinearChannel(ptr %32)
  %34 = load i1, ptr %33, align 1
  %35 = call %Unit @free(ptr %33)
  store i1 %34, ptr %val, align 1
  %36 = load ptr, ptr %c, align 8
  %37 = call %Unit @_ContractChannel(ptr %36)
  %val30 = load i1, ptr %val, align 1
  %carry31 = load i1, ptr %carry, align 1
  %38 = call i1 @XOR(i1 %val30, i1 %carry31)
  %39 = call ptr @malloc(i32 1)
  store i1 %38, ptr %39, align 1
  %40 = load ptr, ptr %c, align 8
  %41 = call %Unit @_WriteChannel(ptr %40, ptr %39)
  %val32 = load i1, ptr %val, align 1
  br i1 %val32, label %prevTrueAnd33, label %mergeBlkAnd36

prevTrueAnd33:                                    ; preds = %loop29
  %carry34 = load i1, ptr %carry, align 1
  br label %mergeBlkAnd36

mergeBlkAnd36:                                    ; preds = %prevTrueAnd33, %loop29
  %logAnd35 = phi i1 [ %val32, %loop29 ], [ %carry34, %prevTrueAnd33 ]
  store i1 %logAnd35, ptr %carry, align 1
  %42 = load ptr, ptr %i1, align 8
  %43 = call i1 @_ShouldLinearLoop(ptr %42)
  br i1 %43, label %loop29, label %rest37

rest37:                                           ; preds = %mergeBlkAnd36, %rest28
  %44 = load ptr, ptr %i2, align 8
  %45 = call i1 @_ShouldLinearLoop(ptr %44)
  br i1 %45, label %loop38, label %rest46

loop38:                                           ; preds = %mergeBlkAnd45, %rest37
  %46 = load ptr, ptr %i2, align 8
  %47 = call ptr @_ReadLinearChannel(ptr %46)
  %48 = load i1, ptr %47, align 1
  %49 = call %Unit @free(ptr %47)
  store i1 %48, ptr %val.0, align 1
  %50 = load ptr, ptr %c, align 8
  %51 = call %Unit @_ContractChannel(ptr %50)
  %val.039 = load i1, ptr %val.0, align 1
  %carry40 = load i1, ptr %carry, align 1
  %52 = call i1 @XOR(i1 %val.039, i1 %carry40)
  %53 = call ptr @malloc(i32 1)
  store i1 %52, ptr %53, align 1
  %54 = load ptr, ptr %c, align 8
  %55 = call %Unit @_WriteChannel(ptr %54, ptr %53)
  %val.041 = load i1, ptr %val.0, align 1
  br i1 %val.041, label %prevTrueAnd42, label %mergeBlkAnd45

prevTrueAnd42:                                    ; preds = %loop38
  %carry43 = load i1, ptr %carry, align 1
  br label %mergeBlkAnd45

mergeBlkAnd45:                                    ; preds = %prevTrueAnd42, %loop38
  %logAnd44 = phi i1 [ %val.041, %loop38 ], [ %carry43, %prevTrueAnd42 ]
  store i1 %logAnd44, ptr %carry, align 1
  %56 = load ptr, ptr %i2, align 8
  %57 = call i1 @_ShouldLinearLoop(ptr %56)
  br i1 %57, label %loop38, label %rest46

rest46:                                           ; preds = %mergeBlkAnd45, %rest37
  %carry47 = load i1, ptr %carry, align 1
  br i1 %carry47, label %then, label %else

then:                                             ; preds = %rest46
  %58 = load ptr, ptr %c, align 8
  %59 = call %Unit @_ContractChannel(ptr %58)
  %carry48 = load i1, ptr %carry, align 1
  %60 = call ptr @malloc(i32 1)
  store i1 %carry48, ptr %60, align 1
  %61 = load ptr, ptr %c, align 8
  %62 = call %Unit @_WriteChannel(ptr %61, ptr %60)
  br label %else

else:                                             ; preds = %then, %rest46
  %63 = load ptr, ptr %c, align 8
  %64 = call %Unit @_WeakenChannel(ptr %63)
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
