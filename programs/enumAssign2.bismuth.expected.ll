; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%a = type { i32, [12 x i8] }
%lambdaOp = type { i32, [8 x i8] }

@0 = private unnamed_addr constant [8 x i8] c"msg=%s\0A\00", align 1
@1 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@2 = private unnamed_addr constant [8 x i8] c"Goodbye\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"Integer: %u\0A\00", align 1
@4 = private unnamed_addr constant [15 x i8] c"Boolean: true\0A\00", align 1
@5 = private unnamed_addr constant [16 x i8] c"Boolean: false\0A\00", align 1
@6 = private unnamed_addr constant [12 x i8] c"String: %s\0A\00", align 1
@7 = private unnamed_addr constant [16 x i8] c"Repeat 2 times!\00", align 1
@8 = private unnamed_addr constant [17 x i8] c"Plain old print!\00", align 1

define %Unit @getPrintLambda(ptr %0) {
entry:
  %fn = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store ptr @"getPrintLambda::#lambda", ptr %fn, align 8
  %fn1 = load ptr, ptr %fn, align 8
  %1 = call ptr @malloc(i32 8)
  store ptr %fn1, ptr %1, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define %Unit @aFromLambdaOp(ptr %0) {
entry:
  %obscured = alloca %a, align 8
  %op = alloca %lambdaOp, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load %lambdaOp, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store %lambdaOp %3, ptr %op, align 4
  %op1 = load %lambdaOp, ptr %op, align 4
  %5 = getelementptr %a, ptr %obscured, i32 0, i32 0
  store i32 3, ptr %5, align 4
  %6 = getelementptr %a, ptr %obscured, i32 0, i32 1
  store %lambdaOp %op1, ptr %6, align 4
  %obscured2 = load %a, ptr %obscured, align 4
  %7 = call ptr @malloc(i32 16)
  store %a %obscured2, ptr %7, align 4
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  ret %Unit zeroinitializer
}

define %Unit @getMain(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @malloc(i32 8)
  store ptr @"getMain::main", ptr %1, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_WriteChannel(ptr %2, ptr %1)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %i = alloca i32, align 4
  %io2 = alloca ptr, align 8
  %mainProg = alloca ptr, align 8
  %io = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @getMain)
  store ptr %1, ptr %io, align 8
  %2 = load ptr, ptr %io, align 8
  %3 = call ptr @_ReadLinearChannel(ptr %2)
  %4 = load ptr, ptr %3, align 8
  %5 = call %Unit @free(ptr %3)
  store ptr %4, ptr %mainProg, align 8
  %mainProg1 = load ptr, ptr %mainProg, align 8
  %6 = call ptr @_Execute(ptr %mainProg1)
  store ptr %6, ptr %io2, align 8
  %7 = load ptr, ptr %io2, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit @free(ptr %8)
  store i32 %9, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %11 = call ptr @malloc(i32 4)
  store i32 %i2, ptr %11, align 4
  %12 = load ptr, ptr %c, align 8
  %13 = call %Unit @_WriteChannel(ptr %12, ptr %11)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private ptr @"getPrintLambda::#lambda"(ptr %0, i32 %1) {
entry:
  %times = alloca i32, align 4
  %msg = alloca ptr, align 8
  store ptr %0, ptr %msg, align 8
  store i32 %1, ptr %times, align 4
  %times1 = load i32, ptr %times, align 4
  %2 = icmp sgt i32 %times1, 0
  br i1 %2, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %msg2 = load ptr, ptr %msg, align 8
  %3 = call i32 (ptr, ...) @printf(ptr @0, ptr %msg2)
  %times3 = load i32, ptr %times, align 4
  %4 = sub nsw i32 %times3, 1
  store i32 %4, ptr %times, align 4
  %times4 = load i32, ptr %times, align 4
  %5 = icmp sgt i32 %times4, 0
  br i1 %5, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %msg5 = load ptr, ptr %msg, align 8
  ret ptr %msg5
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

define private %Unit @"getMain::main"(ptr %0) {
entry:
  %fn.1 = alloca ptr, align 8
  %fn.0 = alloca ptr, align 8
  %1 = alloca %lambdaOp, align 8
  %s.0 = alloca %lambdaOp, align 8
  %s = alloca ptr, align 8
  %b = alloca i1, align 1
  %i = alloca i32, align 4
  %2 = alloca %a, align 8
  %chan3 = alloca ptr, align 8
  %obscured = alloca %a, align 8
  %fn.2 = alloca ptr, align 8
  %fn = alloca ptr, align 8
  %3 = alloca %lambdaOp, align 8
  %chan2 = alloca ptr, align 8
  %op = alloca %lambdaOp, align 8
  %chan = alloca ptr, align 8
  %t2 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %4 = call ptr @_Execute(ptr @getPrintLambda)
  store ptr %4, ptr %chan, align 8
  %5 = load ptr, ptr %chan, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load ptr, ptr %6, align 8
  %8 = call %Unit @free(ptr %6)
  store ptr %7, ptr %t2, align 8
  %9 = call ptr @_Execute(ptr @getPrintLambda)
  store ptr %9, ptr %chan2, align 8
  %10 = load ptr, ptr %chan2, align 8
  %11 = call ptr @_ReadLinearChannel(ptr %10)
  %12 = load ptr, ptr %11, align 8
  %13 = call %Unit @free(ptr %11)
  %14 = getelementptr %lambdaOp, ptr %op, i32 0, i32 0
  store i32 2, ptr %14, align 4
  %15 = getelementptr %lambdaOp, ptr %op, i32 0, i32 1
  store ptr %12, ptr %15, align 8
  %op1 = load %lambdaOp, ptr %op, align 4
  store %lambdaOp %op1, ptr %3, align 4
  %16 = getelementptr %lambdaOp, ptr %3, i32 0, i32 0
  %17 = load i32, ptr %16, align 4
  switch i32 %17, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %18 = getelementptr %lambdaOp, ptr %3, i32 0, i32 1
  %19 = load ptr, ptr %18, align 8
  store ptr %19, ptr %fn, align 8
  %fn2 = load ptr, ptr %fn, align 8
  %20 = call ptr %fn2(ptr @1, i32 2)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %21 = getelementptr %lambdaOp, ptr %3, i32 0, i32 1
  %22 = load ptr, ptr %21, align 8
  store ptr %22, ptr %fn.2, align 8
  %fn.23 = load ptr, ptr %fn.2, align 8
  %23 = call ptr %fn.23(ptr @2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %24 = call ptr @_Execute(ptr @aFromLambdaOp)
  store ptr %24, ptr %chan3, align 8
  %op4 = load %lambdaOp, ptr %op, align 4
  %25 = call ptr @malloc(i32 12)
  store %lambdaOp %op4, ptr %25, align 4
  %26 = load ptr, ptr %chan3, align 8
  %27 = call %Unit @_WriteChannel(ptr %26, ptr %25)
  %28 = load ptr, ptr %chan3, align 8
  %29 = call ptr @_ReadLinearChannel(ptr %28)
  %30 = load %a, ptr %29, align 4
  %31 = call %Unit @free(ptr %29)
  store %a %30, ptr %obscured, align 4
  %obscured5 = load %a, ptr %obscured, align 4
  store %a %obscured5, ptr %2, align 4
  %32 = getelementptr %a, ptr %2, i32 0, i32 0
  %33 = load i32, ptr %32, align 4
  switch i32 %33, label %match-cont17 [
    i32 2, label %tagBranch26
    i32 1, label %tagBranch18
    i32 4, label %tagBranch4
    i32 3, label %tagBranch3
  ]

tagBranch26:                                      ; preds = %match-cont
  %34 = getelementptr %a, ptr %2, i32 0, i32 1
  %35 = load i32, ptr %34, align 4
  store i32 %35, ptr %i, align 4
  %i7 = load i32, ptr %i, align 4
  %36 = call i32 (ptr, ...) @printf(ptr @3, i32 %i7)
  br label %match-cont17

tagBranch18:                                      ; preds = %match-cont
  %37 = getelementptr %a, ptr %2, i32 0, i32 1
  %38 = load i1, ptr %37, align 1
  store i1 %38, ptr %b, align 1
  %b9 = load i1, ptr %b, align 1
  br i1 %b9, label %then, label %else

then:                                             ; preds = %tagBranch18
  %39 = call i32 (ptr, ...) @printf(ptr @4)
  br label %if-cont

else:                                             ; preds = %tagBranch18
  %40 = call i32 (ptr, ...) @printf(ptr @5)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  br label %match-cont17

tagBranch4:                                       ; preds = %match-cont
  %41 = getelementptr %a, ptr %2, i32 0, i32 1
  %42 = load ptr, ptr %41, align 8
  store ptr %42, ptr %s, align 8
  %s10 = load ptr, ptr %s, align 8
  %43 = call i32 (ptr, ...) @printf(ptr @6, ptr %s10)
  br label %match-cont17

tagBranch3:                                       ; preds = %match-cont
  %44 = getelementptr %a, ptr %2, i32 0, i32 1
  %45 = load %lambdaOp, ptr %44, align 4
  store %lambdaOp %45, ptr %s.0, align 4
  %s.011 = load %lambdaOp, ptr %s.0, align 4
  store %lambdaOp %s.011, ptr %1, align 4
  %46 = getelementptr %lambdaOp, ptr %1, i32 0, i32 0
  %47 = load i32, ptr %46, align 4
  switch i32 %47, label %match-cont16 [
    i32 2, label %tagBranch212
    i32 1, label %tagBranch114
  ]

tagBranch212:                                     ; preds = %tagBranch3
  %48 = getelementptr %lambdaOp, ptr %1, i32 0, i32 1
  %49 = load ptr, ptr %48, align 8
  store ptr %49, ptr %fn.0, align 8
  %fn.013 = load ptr, ptr %fn.0, align 8
  %50 = call ptr %fn.013(ptr @7, i32 2)
  br label %match-cont16

tagBranch114:                                     ; preds = %tagBranch3
  %51 = getelementptr %lambdaOp, ptr %1, i32 0, i32 1
  %52 = load ptr, ptr %51, align 8
  store ptr %52, ptr %fn.1, align 8
  %fn.115 = load ptr, ptr %fn.1, align 8
  %53 = call ptr %fn.115(ptr @8)
  br label %match-cont16

match-cont16:                                     ; preds = %tagBranch114, %tagBranch212, %tagBranch3
  br label %match-cont17

match-cont17:                                     ; preds = %match-cont16, %tagBranch4, %if-cont, %tagBranch26, %match-cont
  %54 = call ptr @malloc(i32 4)
  store i32 0, ptr %54, align 4
  %55 = load ptr, ptr %c, align 8
  %56 = call %Unit @_WriteChannel(ptr %55, ptr %54)
  ret %Unit zeroinitializer
}

declare ptr @_Execute(ptr)
