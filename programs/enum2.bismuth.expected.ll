; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(int + str)" = type { i32, [8 x i8] }
%"(str -> str + str, int -> str)" = type { i32, [8 x i8] }
%"programs::enum2::lambdaOp" = type { i32, [8 x i8] }
%"programs::enum2::a" = type { i32, [12 x i8] }

@0 = private unnamed_addr constant [8 x i8] c"msg=%s\0A\00", align 1
@1 = private unnamed_addr constant [6 x i8] c"Hello\00", align 1
@2 = private unnamed_addr constant [8 x i8] c"Goodbye\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"Integer: %u\0A\00", align 1
@4 = private unnamed_addr constant [15 x i8] c"Boolean: true\0A\00", align 1
@5 = private unnamed_addr constant [16 x i8] c"Boolean: false\0A\00", align 1
@6 = private unnamed_addr constant [12 x i8] c"String: %s\0A\00", align 1
@7 = private unnamed_addr constant [18 x i8] c"Got regular sum!\0A\00", align 1
@8 = private unnamed_addr constant [16 x i8] c"Repeat 2 times!\00", align 1
@9 = private unnamed_addr constant [17 x i8] c"Plain old print!\00", align 1

define %Unit @program(ptr %0) {
entry:
  %AAAA2 = alloca %"(int + str)", align 8
  %AAAA1 = alloca %"(int + str)", align 8
  %op322 = alloca %"(str -> str + str, int -> str)", align 8
  %op2 = alloca %"(str -> str + str, int -> str)", align 8
  %fn.2 = alloca ptr, align 8
  %fn.1 = alloca ptr, align 8
  %1 = alloca %"programs::enum2::lambdaOp", align 8
  %s.1 = alloca %"programs::enum2::lambdaOp", align 8
  %s.0 = alloca %"(str -> str + str, int -> str)", align 8
  %s = alloca ptr, align 8
  %b = alloca i1, align 1
  %i = alloca i32, align 4
  %2 = alloca %"programs::enum2::a", align 8
  %obscured = alloca %"programs::enum2::a", align 8
  %fn.3 = alloca ptr, align 8
  %fn.0 = alloca ptr, align 8
  %3 = alloca %"programs::enum2::lambdaOp", align 8
  %op = alloca %"programs::enum2::lambdaOp", align 8
  %t2 = alloca ptr, align 8
  %fn = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store ptr @"program::#lambda", ptr %fn, align 8
  %fn1 = load ptr, ptr %fn, align 8
  store ptr %fn1, ptr %t2, align 8
  %fn2 = load ptr, ptr %fn, align 8
  %4 = getelementptr %"programs::enum2::lambdaOp", ptr %op, i32 0, i32 0
  store i32 2, ptr %4, align 4
  %5 = getelementptr %"programs::enum2::lambdaOp", ptr %op, i32 0, i32 1
  store ptr %fn2, ptr %5, align 8
  %op3 = load %"programs::enum2::lambdaOp", ptr %op, align 4
  store %"programs::enum2::lambdaOp" %op3, ptr %3, align 4
  %6 = getelementptr %"programs::enum2::lambdaOp", ptr %3, i32 0, i32 0
  %7 = load i32, ptr %6, align 4
  switch i32 %7, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %8 = getelementptr %"programs::enum2::lambdaOp", ptr %3, i32 0, i32 1
  %9 = load ptr, ptr %8, align 8
  store ptr %9, ptr %fn.0, align 8
  %fn.04 = load ptr, ptr %fn.0, align 8
  %10 = call ptr %fn.04(ptr @1, i32 2)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %11 = getelementptr %"programs::enum2::lambdaOp", ptr %3, i32 0, i32 1
  %12 = load ptr, ptr %11, align 8
  store ptr %12, ptr %fn.3, align 8
  %fn.35 = load ptr, ptr %fn.3, align 8
  %13 = call ptr %fn.35(ptr @2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %op6 = load %"programs::enum2::lambdaOp", ptr %op, align 4
  %14 = getelementptr %"programs::enum2::a", ptr %obscured, i32 0, i32 0
  store i32 4, ptr %14, align 4
  %15 = getelementptr %"programs::enum2::a", ptr %obscured, i32 0, i32 1
  store %"programs::enum2::lambdaOp" %op6, ptr %15, align 4
  %obscured7 = load %"programs::enum2::a", ptr %obscured, align 4
  store %"programs::enum2::a" %obscured7, ptr %2, align 4
  %16 = getelementptr %"programs::enum2::a", ptr %2, i32 0, i32 0
  %17 = load i32, ptr %16, align 4
  switch i32 %17, label %match-cont19 [
    i32 3, label %tagBranch3
    i32 2, label %tagBranch29
    i32 5, label %tagBranch5
    i32 1, label %tagBranch112
    i32 4, label %tagBranch4
  ]

tagBranch3:                                       ; preds = %match-cont
  %18 = getelementptr %"programs::enum2::a", ptr %2, i32 0, i32 1
  %19 = load i32, ptr %18, align 4
  store i32 %19, ptr %i, align 4
  %i8 = load i32, ptr %i, align 4
  %20 = call i32 (ptr, ...) @printf(ptr @3, i32 %i8)
  br label %match-cont19

tagBranch29:                                      ; preds = %match-cont
  %21 = getelementptr %"programs::enum2::a", ptr %2, i32 0, i32 1
  %22 = load i1, ptr %21, align 1
  store i1 %22, ptr %b, align 1
  %b10 = load i1, ptr %b, align 1
  br i1 %b10, label %then, label %else

then:                                             ; preds = %tagBranch29
  %23 = call i32 (ptr, ...) @printf(ptr @4)
  br label %if-cont

else:                                             ; preds = %tagBranch29
  %24 = call i32 (ptr, ...) @printf(ptr @5)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  br label %match-cont19

tagBranch5:                                       ; preds = %match-cont
  %25 = getelementptr %"programs::enum2::a", ptr %2, i32 0, i32 1
  %26 = load ptr, ptr %25, align 8
  store ptr %26, ptr %s, align 8
  %s11 = load ptr, ptr %s, align 8
  %27 = call i32 (ptr, ...) @printf(ptr @6, ptr %s11)
  br label %match-cont19

tagBranch112:                                     ; preds = %match-cont
  %28 = getelementptr %"programs::enum2::a", ptr %2, i32 0, i32 1
  %29 = load %"(str -> str + str, int -> str)", ptr %28, align 4
  store %"(str -> str + str, int -> str)" %29, ptr %s.0, align 4
  %30 = call i32 (ptr, ...) @printf(ptr @7)
  br label %match-cont19

tagBranch4:                                       ; preds = %match-cont
  %31 = getelementptr %"programs::enum2::a", ptr %2, i32 0, i32 1
  %32 = load %"programs::enum2::lambdaOp", ptr %31, align 4
  store %"programs::enum2::lambdaOp" %32, ptr %s.1, align 4
  %s.113 = load %"programs::enum2::lambdaOp", ptr %s.1, align 4
  store %"programs::enum2::lambdaOp" %s.113, ptr %1, align 4
  %33 = getelementptr %"programs::enum2::lambdaOp", ptr %1, i32 0, i32 0
  %34 = load i32, ptr %33, align 4
  switch i32 %34, label %match-cont18 [
    i32 2, label %tagBranch214
    i32 1, label %tagBranch116
  ]

tagBranch214:                                     ; preds = %tagBranch4
  %35 = getelementptr %"programs::enum2::lambdaOp", ptr %1, i32 0, i32 1
  %36 = load ptr, ptr %35, align 8
  store ptr %36, ptr %fn.1, align 8
  %fn.115 = load ptr, ptr %fn.1, align 8
  %37 = call ptr %fn.115(ptr @8, i32 2)
  br label %match-cont18

tagBranch116:                                     ; preds = %tagBranch4
  %38 = getelementptr %"programs::enum2::lambdaOp", ptr %1, i32 0, i32 1
  %39 = load ptr, ptr %38, align 8
  store ptr %39, ptr %fn.2, align 8
  %fn.217 = load ptr, ptr %fn.2, align 8
  %40 = call ptr %fn.217(ptr @9)
  br label %match-cont18

match-cont18:                                     ; preds = %tagBranch116, %tagBranch214, %tagBranch4
  br label %match-cont19

match-cont19:                                     ; preds = %match-cont18, %tagBranch112, %tagBranch5, %if-cont, %tagBranch3, %match-cont
  %fn20 = load ptr, ptr %fn, align 8
  %41 = getelementptr %"(str -> str + str, int -> str)", ptr %op2, i32 0, i32 0
  store i32 2, ptr %41, align 4
  %42 = getelementptr %"(str -> str + str, int -> str)", ptr %op2, i32 0, i32 1
  store ptr %fn20, ptr %42, align 8
  %op221 = load %"(str -> str + str, int -> str)", ptr %op2, align 4
  store %"(str -> str + str, int -> str)" %op221, ptr %op322, align 4
  %43 = getelementptr %"(int + str)", ptr %AAAA1, i32 0, i32 0
  store i32 1, ptr %43, align 4
  %44 = getelementptr %"(int + str)", ptr %AAAA1, i32 0, i32 1
  store i32 10, ptr %44, align 4
  %AAAA123 = load %"(int + str)", ptr %AAAA1, align 4
  store %"(int + str)" %AAAA123, ptr %AAAA2, align 4
  %op224 = load %"(str -> str + str, int -> str)", ptr %op2, align 4
  store %"(str -> str + str, int -> str)" %op224, ptr %op, align 4
  %45 = call ptr @malloc(i32 4)
  store i32 0, ptr %45, align 4
  %46 = load ptr, ptr %c, align 8
  %47 = call %Unit @_WriteChannel(ptr %46, ptr %45)
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
