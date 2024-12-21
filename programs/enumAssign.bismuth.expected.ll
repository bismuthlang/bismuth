; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"programs::enumAssign::lambdaOp" = type { i32, [8 x i8] }
%"programs::enumAssign::a" = type { i32, [12 x i8] }

@0 = private unnamed_addr constant [8 x i8] c"msg=%s\0A\00", align 1
@1 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@2 = private unnamed_addr constant [8 x i8] c"Goodbye\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"Integer: %u\0A\00", align 1
@4 = private unnamed_addr constant [15 x i8] c"Boolean: true\0A\00", align 1
@5 = private unnamed_addr constant [16 x i8] c"Boolean: false\0A\00", align 1
@6 = private unnamed_addr constant [12 x i8] c"String: %s\0A\00", align 1
@7 = private unnamed_addr constant [16 x i8] c"Repeat 2 times!\00", align 1
@8 = private unnamed_addr constant [17 x i8] c"Plain old print!\00", align 1

define %Unit @program(ptr %0) {
entry:
  %fn.2 = alloca ptr, align 8
  %fn.1 = alloca ptr, align 8
  %1 = alloca %"programs::enumAssign::lambdaOp", align 8
  %s.0 = alloca %"programs::enumAssign::lambdaOp", align 8
  %s = alloca ptr, align 8
  %b = alloca i1, align 1
  %i = alloca i32, align 4
  %2 = alloca %"programs::enumAssign::a", align 8
  %obscured = alloca %"programs::enumAssign::a", align 8
  %fn.3 = alloca ptr, align 8
  %fn.0 = alloca ptr, align 8
  %3 = alloca %"programs::enumAssign::lambdaOp", align 8
  %op = alloca %"programs::enumAssign::lambdaOp", align 8
  %t2 = alloca ptr, align 8
  %fn = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store ptr @"program::#lambda", ptr %fn, align 8
  %fn1 = load ptr, ptr %fn, align 8
  store ptr %fn1, ptr %t2, align 8
  %fn2 = load ptr, ptr %fn, align 8
  %4 = getelementptr %"programs::enumAssign::lambdaOp", ptr %op, i32 0, i32 0
  store i32 1, ptr %4, align 4
  %5 = getelementptr %"programs::enumAssign::lambdaOp", ptr %op, i32 0, i32 1
  store ptr %fn2, ptr %5, align 8
  %op3 = load %"programs::enumAssign::lambdaOp", ptr %op, align 4
  store %"programs::enumAssign::lambdaOp" %op3, ptr %3, align 4
  %6 = getelementptr %"programs::enumAssign::lambdaOp", ptr %3, i32 0, i32 0
  %7 = load i32, ptr %6, align 4
  switch i32 %7, label %match-cont [
    i32 1, label %tagBranch1
    i32 1, label %tagBranch15
  ]

tagBranch1:                                       ; preds = %entry
  %8 = getelementptr %"programs::enumAssign::lambdaOp", ptr %3, i32 0, i32 1
  %9 = load ptr, ptr %8, align 8
  store ptr %9, ptr %fn.0, align 8
  %fn.04 = load ptr, ptr %fn.0, align 8
  %10 = call ptr %fn.04(ptr @1, i32 2)
  br label %match-cont

tagBranch15:                                      ; preds = %entry
  %11 = getelementptr %"programs::enumAssign::lambdaOp", ptr %3, i32 0, i32 1
  %12 = load ptr, ptr %11, align 8
  store ptr %12, ptr %fn.3, align 8
  %fn.36 = load ptr, ptr %fn.3, align 8
  %13 = call ptr %fn.36(ptr @2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch15, %tagBranch1, %entry
  %op7 = load %"programs::enumAssign::lambdaOp", ptr %op, align 4
  %14 = getelementptr %"programs::enumAssign::a", ptr %obscured, i32 0, i32 0
  store i32 3, ptr %14, align 4
  %15 = getelementptr %"programs::enumAssign::a", ptr %obscured, i32 0, i32 1
  store %"programs::enumAssign::lambdaOp" %op7, ptr %15, align 4
  %obscured8 = load %"programs::enumAssign::a", ptr %obscured, align 4
  store %"programs::enumAssign::a" %obscured8, ptr %2, align 4
  %16 = getelementptr %"programs::enumAssign::a", ptr %2, i32 0, i32 0
  %17 = load i32, ptr %16, align 4
  switch i32 %17, label %match-cont19 [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch110
    i32 4, label %tagBranch4
    i32 3, label %tagBranch3
  ]

tagBranch2:                                       ; preds = %match-cont
  %18 = getelementptr %"programs::enumAssign::a", ptr %2, i32 0, i32 1
  %19 = load i32, ptr %18, align 4
  store i32 %19, ptr %i, align 4
  %i9 = load i32, ptr %i, align 4
  %20 = call i32 (ptr, ...) @printf(ptr @3, i32 %i9)
  br label %match-cont19

tagBranch110:                                     ; preds = %match-cont
  %21 = getelementptr %"programs::enumAssign::a", ptr %2, i32 0, i32 1
  %22 = load i1, ptr %21, align 1
  store i1 %22, ptr %b, align 1
  %b11 = load i1, ptr %b, align 1
  br i1 %b11, label %then, label %else

then:                                             ; preds = %tagBranch110
  %23 = call i32 (ptr, ...) @printf(ptr @4)
  br label %if-cont

else:                                             ; preds = %tagBranch110
  %24 = call i32 (ptr, ...) @printf(ptr @5)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  br label %match-cont19

tagBranch4:                                       ; preds = %match-cont
  %25 = getelementptr %"programs::enumAssign::a", ptr %2, i32 0, i32 1
  %26 = load ptr, ptr %25, align 8
  store ptr %26, ptr %s, align 8
  %s12 = load ptr, ptr %s, align 8
  %27 = call i32 (ptr, ...) @printf(ptr @6, ptr %s12)
  br label %match-cont19

tagBranch3:                                       ; preds = %match-cont
  %28 = getelementptr %"programs::enumAssign::a", ptr %2, i32 0, i32 1
  %29 = load %"programs::enumAssign::lambdaOp", ptr %28, align 4
  store %"programs::enumAssign::lambdaOp" %29, ptr %s.0, align 4
  %s.013 = load %"programs::enumAssign::lambdaOp", ptr %s.0, align 4
  store %"programs::enumAssign::lambdaOp" %s.013, ptr %1, align 4
  %30 = getelementptr %"programs::enumAssign::lambdaOp", ptr %1, i32 0, i32 0
  %31 = load i32, ptr %30, align 4
  switch i32 %31, label %match-cont18 [
    i32 1, label %tagBranch114
    i32 1, label %tagBranch116
  ]

tagBranch114:                                     ; preds = %tagBranch3
  %32 = getelementptr %"programs::enumAssign::lambdaOp", ptr %1, i32 0, i32 1
  %33 = load ptr, ptr %32, align 8
  store ptr %33, ptr %fn.1, align 8
  %fn.115 = load ptr, ptr %fn.1, align 8
  %34 = call ptr %fn.115(ptr @7, i32 2)
  br label %match-cont18

tagBranch116:                                     ; preds = %tagBranch3
  %35 = getelementptr %"programs::enumAssign::lambdaOp", ptr %1, i32 0, i32 1
  %36 = load ptr, ptr %35, align 8
  store ptr %36, ptr %fn.2, align 8
  %fn.217 = load ptr, ptr %fn.2, align 8
  %37 = call ptr %fn.217(ptr @8)
  br label %match-cont18

match-cont18:                                     ; preds = %tagBranch116, %tagBranch114, %tagBranch3
  br label %match-cont19

match-cont19:                                     ; preds = %match-cont18, %tagBranch4, %if-cont, %tagBranch2, %match-cont
  %38 = call ptr @malloc(i32 4)
  store i32 0, ptr %38, align 4
  %39 = load ptr, ptr %c, align 8
  %40 = call %Unit @_WriteChannel(ptr %39, ptr %38)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private ptr @"program::#lambda"(ptr %0, i32 %1) {
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
