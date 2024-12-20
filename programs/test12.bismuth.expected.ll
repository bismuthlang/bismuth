; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [23 x i8] c"%d is the %dth prime!\0A\00", align 1

define %Unit @isPrime(ptr %0) {
entry:
  %ans = alloca i1, align 1
  %done = alloca i1, align 1
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %n, align 4
  store i32 3, ptr %i, align 4
  store i1 false, ptr %done, align 1
  store i1 true, ptr %ans, align 1
  %done1 = load i1, ptr %done, align 1
  %5 = xor i1 %done1, true
  br i1 %5, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %entry
  %i2 = load i32, ptr %i, align 4
  %n3 = load i32, ptr %n, align 4
  %6 = icmp slt i32 %i2, %n3
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %prevTrueAnd, %entry
  %logAnd = phi i1 [ %5, %entry ], [ %6, %prevTrueAnd ]
  br i1 %logAnd, label %loop, label %rest

loop:                                             ; preds = %mergeBlkAnd14, %mergeBlkAnd
  %n4 = load i32, ptr %n, align 4
  %i5 = load i32, ptr %i, align 4
  %7 = sdiv i32 %n4, %i5
  %i6 = load i32, ptr %i, align 4
  %8 = mul nsw i32 %7, %i6
  %n7 = load i32, ptr %n, align 4
  %9 = icmp eq i32 %8, %n7
  br i1 %9, label %then, label %else

then:                                             ; preds = %loop
  store i1 true, ptr %done, align 1
  store i1 false, ptr %ans, align 1
  br label %if-cont

else:                                             ; preds = %loop
  %i8 = load i32, ptr %i, align 4
  %10 = add nsw i32 %i8, 2
  store i32 %10, ptr %i, align 4
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %done9 = load i1, ptr %done, align 1
  %11 = xor i1 %done9, true
  br i1 %11, label %prevTrueAnd10, label %mergeBlkAnd14

prevTrueAnd10:                                    ; preds = %if-cont
  %i11 = load i32, ptr %i, align 4
  %n12 = load i32, ptr %n, align 4
  %12 = icmp slt i32 %i11, %n12
  br label %mergeBlkAnd14

mergeBlkAnd14:                                    ; preds = %prevTrueAnd10, %if-cont
  %logAnd13 = phi i1 [ %11, %if-cont ], [ %12, %prevTrueAnd10 ]
  br i1 %logAnd13, label %loop, label %rest

rest:                                             ; preds = %mergeBlkAnd14, %mergeBlkAnd
  %ans15 = load i1, ptr %ans, align 1
  %13 = call ptr @malloc(i32 1)
  store i1 %ans15, ptr %13, align 1
  %14 = load ptr, ptr %c, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %ans = alloca i1, align 1
  %c1 = alloca ptr, align 8
  %nPrimes = alloca i32, align 4
  %current = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 3, ptr %current, align 4
  store i32 2, ptr %nPrimes, align 4
  %current1 = load i32, ptr %current, align 4
  %1 = icmp slt i32 %current1, 100
  br i1 %1, label %loop, label %rest

loop:                                             ; preds = %else, %entry
  %2 = call ptr @_Execute(ptr @isPrime)
  store ptr %2, ptr %c1, align 8
  %current2 = load i32, ptr %current, align 4
  %3 = call ptr @malloc(i32 4)
  store i32 %current2, ptr %3, align 4
  %4 = load ptr, ptr %c1, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = load ptr, ptr %c1, align 8
  %7 = call ptr @_ReadLinearChannel(ptr %6)
  %8 = load i1, ptr %7, align 1
  %9 = call %Unit @free(ptr %7)
  store i1 %8, ptr %ans, align 1
  %ans3 = load i1, ptr %ans, align 1
  br i1 %ans3, label %then, label %else

then:                                             ; preds = %loop
  %current4 = load i32, ptr %current, align 4
  %nPrimes5 = load i32, ptr %nPrimes, align 4
  %10 = call i32 (...) @printf(ptr @0, i32 %current4, i32 %nPrimes5)
  %nPrimes6 = load i32, ptr %nPrimes, align 4
  %11 = add nsw i32 %nPrimes6, 1
  store i32 %11, ptr %nPrimes, align 4
  br label %else

else:                                             ; preds = %then, %loop
  %current7 = load i32, ptr %current, align 4
  %12 = add nsw i32 %current7, 2
  store i32 %12, ptr %current, align 4
  %current8 = load i32, ptr %current, align 4
  %13 = icmp slt i32 %current8, 100
  br i1 %13, label %loop, label %rest

rest:                                             ; preds = %else, %entry
  %nPrimes9 = load i32, ptr %nPrimes, align 4
  %14 = call ptr @malloc(i32 4)
  store i32 %nPrimes9, ptr %14, align 4
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
