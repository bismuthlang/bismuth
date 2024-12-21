; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%E1 = type { i32, [8 x i8] }
%E2 = type { i32, [12 x i8] }

@0 = private unnamed_addr constant [9 x i8] c"int: %u\0A\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"str: %s\0A\00", align 1
@2 = private unnamed_addr constant [10 x i8] c"bool: %s\0A\00", align 1
@3 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@4 = private unnamed_addr constant [6 x i8] c"false\00", align 1

define %Unit @program(ptr %0) {
entry:
  %b = alloca i1, align 1
  %s = alloca ptr, align 8
  %i = alloca i32, align 4
  %1 = alloca %E1, align 8
  %e = alloca %E1, align 8
  %2 = alloca %E2, align 8
  %e2a = alloca %E2, align 8
  %e2 = alloca %E2, align 8
  %e1 = alloca %E1, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = getelementptr %E1, ptr %e1, i32 0, i32 0
  store i32 1, ptr %3, align 4
  %4 = getelementptr %E1, ptr %e1, i32 0, i32 1
  store i32 10, ptr %4, align 4
  %5 = getelementptr %E2, ptr %e2, i32 0, i32 0
  store i32 2, ptr %5, align 4
  %6 = getelementptr %E2, ptr %e2, i32 0, i32 1
  store i1 false, ptr %6, align 1
  %e21 = load %E2, ptr %e2, align 4
  store %E2 %e21, ptr %e2a, align 4
  %e2a2 = load %E2, ptr %e2a, align 4
  store %E2 %e2a2, ptr %2, align 4
  %7 = getelementptr %E2, ptr %2, i32 0, i32 0
  %8 = load i32, ptr %7, align 4
  switch i32 %8, label %match-cont9 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch27
  ]

tagBranch1:                                       ; preds = %entry
  %9 = getelementptr %E2, ptr %2, i32 0, i32 1
  %10 = load %E1, ptr %9, align 4
  store %E1 %10, ptr %e, align 4
  %e3 = load %E1, ptr %e, align 4
  store %E1 %e3, ptr %1, align 4
  %11 = getelementptr %E1, ptr %1, i32 0, i32 0
  %12 = load i32, ptr %11, align 4
  switch i32 %12, label %match-cont [
    i32 1, label %tagBranch14
    i32 2, label %tagBranch2
  ]

tagBranch14:                                      ; preds = %tagBranch1
  %13 = getelementptr %E1, ptr %1, i32 0, i32 1
  %14 = load i32, ptr %13, align 4
  store i32 %14, ptr %i, align 4
  %i5 = load i32, ptr %i, align 4
  %15 = call i32 (ptr, ...) @printf(ptr @0, i32 %i5)
  br label %match-cont

tagBranch2:                                       ; preds = %tagBranch1
  %16 = getelementptr %E1, ptr %1, i32 0, i32 1
  %17 = load ptr, ptr %16, align 8
  store ptr %17, ptr %s, align 8
  %s6 = load ptr, ptr %s, align 8
  %18 = call i32 (ptr, ...) @printf(ptr @1, ptr %s6)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch14, %tagBranch1
  br label %match-cont9

tagBranch27:                                      ; preds = %entry
  %19 = getelementptr %E2, ptr %2, i32 0, i32 1
  %20 = load i1, ptr %19, align 1
  store i1 %20, ptr %b, align 1
  %b8 = load i1, ptr %b, align 1
  %21 = call ptr @"program::#lambda"(i1 %b8)
  %22 = call i32 (ptr, ...) @printf(ptr @2, ptr %21)
  br label %match-cont9

match-cont9:                                      ; preds = %tagBranch27, %match-cont, %entry
  %23 = call ptr @malloc(i32 4)
  store i32 0, ptr %23, align 4
  %24 = load ptr, ptr %c, align 8
  %25 = call %Unit @_WriteChannel(ptr %24, ptr %23)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private ptr @"program::#lambda"(i1 %0) {
entry:
  %b = alloca i1, align 1
  store i1 %0, ptr %b, align 1
  %b1 = load i1, ptr %b, align 1
  br i1 %b1, label %then, label %else

then:                                             ; preds = %entry
  ret ptr @3

else:                                             ; preds = %entry
  ret ptr @4
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
