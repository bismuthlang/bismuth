; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%"(boolean + int)" = type { i32, [4 x i8] }
%Unit = type {}

@0 = private unnamed_addr constant [13 x i8] c"integer: %u\0A\00", align 1
@1 = private unnamed_addr constant [13 x i8] c"boolean: %s\0A\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@3 = private unnamed_addr constant [6 x i8] c"false\00", align 1

define i32 @"programs::adv::enumPassing-fn::test"(%"(boolean + int)" %0) {
entry:
  %b = alloca i1, align 1
  %i = alloca i32, align 4
  %1 = alloca %"(boolean + int)", align 8
  %sum = alloca %"(boolean + int)", align 8
  store %"(boolean + int)" %0, ptr %sum, align 4
  %sum1 = load %"(boolean + int)", ptr %sum, align 4
  store %"(boolean + int)" %sum1, ptr %1, align 4
  %2 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 0
  %3 = load %"(boolean + int)", ptr %2, align 4
  switch %"(boolean + int)" %3, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %4 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 1
  %5 = load i32, ptr %4, align 4
  store i32 %5, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %6 = call i32 (ptr, ...) @printf(ptr @0, i32 %i2)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %7 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 1
  %8 = load i1, ptr %7, align 1
  store i1 %8, ptr %b, align 1
  %b3 = load i1, ptr %b, align 1
  %9 = call ptr @"programs::adv::enumPassing-fn::test::#lambda"(i1 %b3)
  %10 = call i32 (ptr, ...) @printf(ptr @1, ptr %9)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %11 = sub nsw i32 0, 1
  ret i32 %11
}

define %Unit @program(ptr %0) {
entry:
  %1 = alloca %"(boolean + int)", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = getelementptr i32, ptr %1, i32 0, i32 0
  store i32 2, ptr %2, align 4
  %3 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 1
  store i32 5, ptr %3, align 4
  %4 = load %"(boolean + int)", ptr %1, align 4
  %5 = call i32 @"programs::adv::enumPassing-fn::test"(%"(boolean + int)" %4)
  %6 = call ptr @malloc(i32 4)
  store i32 0, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private ptr @"programs::adv::enumPassing-fn::test::#lambda"(i1 %0) {
entry:
  %b = alloca i1, align 1
  store i1 %0, ptr %b, align 1
  %b1 = load i1, ptr %b, align 1
  br i1 %b1, label %then, label %else

then:                                             ; preds = %entry
  ret ptr @2

else:                                             ; preds = %entry
  ret ptr @3
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
